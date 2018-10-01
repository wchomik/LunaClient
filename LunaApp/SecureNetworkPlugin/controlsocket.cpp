#include "controlsocket.h"

#include <QSslEllipticCurve>
#include <QSslCipher>
#include <QFile>

QByteArray readResource(QString const & path)
{
    QFile resource(path);
    resource.open(QIODevice::ReadOnly);
    return resource.readAll();
}

template<typename C, typename V>
bool contains(C && container, V && value)
{
    return std::find(std::begin(container), std::end(container), value) != std::end(container);
}

ControlSocket::ControlSocket(QHostAddress address, uint16_t port, luna::client::Listener *listener) :
    mLocalCertificate(readResource(":/SecureNetwork/own.crt")),
    mCaCertificate(readResource(":/SecureNetwork/own.key")),
    mPrivateKey(readResource(":/SecureNetwork/own.key"), QSsl::KeyAlgorithm::Ec),
    mConfiguration(),
    mSslSink(&mSocket),
    mEncoder(&mSslSink),
    mDecoder(listener),
    mDefragmenter(&mDecoder)
{
    mConfiguration.setCaCertificates({mCaCertificate});
    mConfiguration.setLocalCertificate(mLocalCertificate);
    mConfiguration.setPrivateKey(mPrivateKey);
    mConfiguration.setCiphers(QSslConfiguration::supportedCiphers());
    mConfiguration.setPeerVerifyMode(QSslSocket::PeerVerifyMode::VerifyPeer);
    mConfiguration.setProtocol(QSsl::SslProtocol::TlsV1_2OrLater);

    mSocket.setSslConfiguration(mConfiguration);

    QObject::connect(&mSocket, QOverload<QList<QSslError> const &>::of(&QSslSocket::sslErrors),
        this, &ControlSocket::handleSslErrors);

    QObject::connect(&mSocket, &QSslSocket::connected,
        this, &ControlSocket::handleTcpConnected);

    QObject::connect(&mSocket, &QSslSocket::encrypted,
        this, &ControlSocket::handleSslConnected);

    QObject::connect(&mSocket, &QSslSocket::disconnected,
        this, &ControlSocket::disconnected);

    mSocket.connectToHost(address, port);
}

QHostAddress ControlSocket::peerAddress() const
{
    return mSocket.peerAddress();
}

luna::client::Encoder &ControlSocket::encoder()
{
    return mEncoder;
}

void ControlSocket::handleSslErrors(const QList<QSslError> &errors)
{
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

    mSocket.ignoreSslErrors(errorsToIgnore);
}

void ControlSocket::handleTcpConnected()
{
    mSocket.startClientEncryption();
}

void ControlSocket::handleSslConnected()
{
    qDebug() << "Encrypted";
    QObject::connect(&mSocket, &QSslSocket::readyRead,
        this, &ControlSocket::readSocket);

    mEncoder.requestStrandConfiguration();
}

void ControlSocket::readSocket()
{
    auto buffer = mSocket.readAll();
    qDebug() << "Read" << buffer.size();

    mDefragmenter.receiveStream(reinterpret_cast<uint8_t const *>(buffer.data()),
        static_cast<size_t>(buffer.size()));
}
