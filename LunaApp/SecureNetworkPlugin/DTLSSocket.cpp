#include "DTLSSocket.hpp"

#include <QSslPreSharedKeyAuthenticator>
#include <QSslConfiguration>
#include <QSslCipher>
#include <QSslEllipticCurve>
#include <QFile>
#include <QDebug>

static QByteArray readResource(QString const & path)
{
    QFile resource(path);
    resource.open(QIODevice::ReadOnly);
    return resource.readAll();
}

DtlsSocket::DtlsSocket(QHostAddress const & address, uint16_t port) :
    mLocalCertificate(readResource(":/SecureNetwork/own.crt")),
    mCaCertificate(readResource(":/SecureNetwork/ca.crt")),
    mPrivateKey(readResource(":/SecureNetwork/own.key"), QSsl::KeyAlgorithm::Ec),
    mSocket(),
    mDtls(QSslSocket::SslClientMode),
    mConnected(false),
    mTimeoutCount(0)
{
    mSocket.connectToHost(address, port);

    auto configuration = QSslConfiguration::defaultDtlsConfiguration();

//    configuration.setCaCertificates({mCaCertificate});
    configuration.setLocalCertificate(mLocalCertificate);
    configuration.setPrivateKey(mPrivateKey);
    configuration.setPeerVerifyMode(QSslSocket::VerifyPeer);
    configuration.setProtocol(QSsl::SslProtocol::DtlsV1_2);
    mDtls.setDtlsConfiguration(configuration);
    mDtls.setPeer(address, port);

    QObject::connect(&mDtls, &QDtls::handshakeTimeout,
        this, &DtlsSocket::handleHandshakeTimeout);

    QObject::connect(&mSocket, &QUdpSocket::readyRead,
        this, &DtlsSocket::handleDatagram);

    mStep = &DtlsSocket::doHandshake;

    mDtls.doHandshake(&mSocket);
}

DtlsSocket::~DtlsSocket()
{
    mDtls.shutdown(&mSocket);
}

void DtlsSocket::write(uint8_t const * data, size_t dataSize)
{
    if (mDtls.isConnectionEncrypted()) {
        auto buffer = QByteArray::fromRawData(
            reinterpret_cast<char const *>(data),
            static_cast<int>(dataSize));
        mDtls.writeDatagramEncrypted(&mSocket, buffer);
    }
}

void DtlsSocket::handleDatagram()
{
    QByteArray buffer(mSocket.pendingDatagramSize(), Qt::Initialization::Uninitialized);
    mSocket.read(buffer.data(), buffer.size());

    (this->*mStep)(buffer);
}

void DtlsSocket::handleHandshakeTimeout()
{
    ++mTimeoutCount;
    qDebug() << "DTLS Timeout count" << mTimeoutCount;
    if (mTimeoutCount >= 5) {
        connected(false);
    } else {
        mDtls.handleTimeout(&mSocket);
    }
}

void DtlsSocket::doHandshake(const QByteArray &buffer)
{
    mTimeoutCount = 0;
    if (!mDtls.doHandshake(&mSocket, buffer)) {
        qDebug() << "DTLS Error" << (int) mDtls.dtlsError();
        for (auto & e : mDtls.peerVerificationErrors()){
            qDebug() << e << e.certificate().digest();
        }

        mDtls.ignoreVerificationErrors(mDtls.peerVerificationErrors());
        if (!mDtls.resumeHandshake(&mSocket)) {
            qDebug() << "DTLS Resume error";
        }
    }

    if (mDtls.handshakeState() == QDtls::HandshakeComplete) {
        QObject::disconnect(&mDtls, &QDtls::handshakeTimeout,
            this, &DtlsSocket::handleHandshakeTimeout);

        mStep = &DtlsSocket::readDatagram;
        connected(true);
    }
}

void DtlsSocket::readDatagram(QByteArray const & buffer)
{
    QByteArray const plainText = mDtls.decryptDatagram(&mSocket, buffer);
    if (mDtls.dtlsError() != QDtlsError::NoError) {
        connected(false);
    } else {
        dataReady(plainText);
    }
}
