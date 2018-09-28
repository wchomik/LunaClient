#include "securehost.h"

#include <lunacore/strand.h>

#include <QSslEllipticCurve>
#include <QSslCipher>
#include <QFile>
#include <QDebug>

#include <array>
#include <algorithm>

template<typename C, typename V>
bool contains(C && container, V && value)
{
    return std::find(std::begin(container), std::end(container), value) != std::end(container);
}

QByteArray readResource(QString const & path)
{
    QFile resource(path);
    resource.open(QIODevice::ReadOnly);
    return resource.readAll();
}

SecureHost::SecureHost(QHostAddress hostAddress) :
    mLocalCertificate(readResource(":/SecureNetwork/own.crt")),
    mCaCertificate(readResource(":/SecureNetwork/own.key")),
    mPrivateKey(readResource(":/SecureNetwork/own.key"), QSsl::KeyAlgorithm::Ec),
    mConfiguration(),
    mSslSink(&mCommandSocket),
    mEncoder(&mSslSink),
    mDecoder(this),
    mDefragmenter(&mDecoder),
    mConnected(false)
{
    mConfiguration.setCaCertificates({mCaCertificate});
    mConfiguration.setLocalCertificate(mLocalCertificate);
    mConfiguration.setPrivateKey(mPrivateKey);
    mConfiguration.setCiphers(QSslConfiguration::supportedCiphers());
    mConfiguration.setPeerVerifyMode(QSslSocket::PeerVerifyMode::VerifyPeer);
    mConfiguration.setProtocol(QSsl::SslProtocol::TlsV1_2OrLater);

    mCommandSocket.setSslConfiguration(mConfiguration);

    QObject::connect(&mCommandSocket, QOverload<QList<QSslError> const &>::of(&QSslSocket::sslErrors),
        [&socket = mCommandSocket](QList<QSslError> const & errors){
            QSslError::SslError expectedCodes[] = {
                QSslError::SelfSignedCertificate,
                QSslError::CertificateExpired,
                QSslError::CertificateNotYetValid,
                QSslError::HostNameMismatch,
            };

            QList<QSslError> errorsToIgnore;

            for (auto const & error : errors) {
                if (contains(expectedCodes, error.error())) {
                    errorsToIgnore.append(error);
                } else {
                    qDebug() << "Error" << error;
                }
            }
            socket.ignoreSslErrors(errorsToIgnore);
        });

    QObject::connect(&mCommandSocket, &QSslSocket::connected,
        [&socket = mCommandSocket](){
            socket.startClientEncryption();
        });

    QObject::connect(&mCommandSocket, &QSslSocket::encrypted,
        [this](){
            mEncoder.requestStrandConfiguration();
            qDebug() << "Encrypted";
            QObject::connect(&mCommandSocket, &QSslSocket::readyRead,
                [this](){

                    auto buffer = mCommandSocket.readAll();
                    qDebug() << "Read" << buffer.size();

                    mDefragmenter.receiveStream(reinterpret_cast<uint8_t const *>(buffer.data()),
                        static_cast<size_t>(buffer.size()));
                });
        });


    mCommandSocket.connectToHost(hostAddress, 9510);
}

void SecureHost::send()
{
    qDebug() << "Sending data";
    constexpr size_t BUFFER_SIZE = 1024 * 2;
    uint8_t buffer[BUFFER_SIZE];
    luna::ByteStream s(buffer, BUFFER_SIZE);
    for (auto const& data : mStrands) {
        auto & strand = data.strand;
        luna::Color * pixels = strand->pixels();
        luna::Color error = luna::Color::Zero();
        luna::ColorChannels channels = strand->config().colorChannels;

        int range;
        std::function<void(luna::ByteStream &, luna::ColorScalar)> writer;
        switch (data.bitDepth) {
            case luna::BitDepth::integer8: {
                range = (1 << 8) - 1;
                writer = [](luna::ByteStream & s, luna::ColorScalar value) {
                    s << static_cast<uint8_t>(value);
                };
                break;
            }
        case luna::BitDepth::integer16: {
                range = (1 << 16) - 1;
                writer = [](luna::ByteStream & s, luna::ColorScalar value) {
                    s << static_cast<uint16_t>(value);
                };
                break;
            }
            default: throw std::out_of_range("Enum value out of range");
        }

        size_t const pixelCount = strand->config().count;
        for (size_t i = 0; i < pixelCount; ++i){
            luna::Color corrected = pixels[i] * range + error;
            luna::Color clampedRounded = corrected.array().max(0).min(range).round().matrix();
            error = corrected - clampedRounded;

            for (int j = 0; j< 4; ++j) {
                if (0 != ((1 << j) & channels)) {
                    writer(s, clampedRounded(j));
                }
            }
        }
    }

    if (s.size() > 0) {
        qDebug() << "Sending" << s.size() << "bytes";
        mDataSocket->write(s.data(), s.size());
    }
}


SecureHost::~SecureHost() = default;

std::string SecureHost::displayName() const
{
    return "Secure";
}

void SecureHost::connect()
{
}

void SecureHost::disconnect()
{
}

bool SecureHost::isConnected() const
{
    return mConnected;
}

void SecureHost::getStrands(std::vector<luna::Strand *> & strands)
{
    for (auto & strand : mStrands) {
        strands.emplace_back(strand.strand.get());
    }
}


void SecureHost::strandConfigurationReceived(const luna::LunaConfiguration &configuration)
{
    for (auto const & strand : configuration.strands) {
        luna::Strand::Config config;
        config.colorSpace = luna::ColorSpace::ws2812();
        config.colorChannels = static_cast<luna::ColorChannels>(strand.colorChannels);
        config.count = strand.count;
        config.begin = Eigen::Vector3f(1, 2, 3);
        config.end = Eigen::Vector3f(4, 5, 6);
        auto s = std::make_unique<luna::Strand>(config);
        mStrands.emplace_back(StrandData{std::move(s), strand.bitDepth});
    }
    mEncoder.requestDataChannel();
}

void SecureHost::dataChannelOpened(const luna::DataChannelConfiguration &configuration)
{
    QByteArray key(reinterpret_cast<char const *>(configuration.sharedKey.data()),
        static_cast<int>(configuration.sharedKey.size()));

    mDataSocket = std::make_unique<DtlsSocket>(mCommandSocket.peerAddress(), configuration.port, key);
    mConnected = true;
}
