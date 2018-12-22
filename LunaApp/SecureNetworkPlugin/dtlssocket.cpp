#include "dtlssocket.h"

#include <QSslPreSharedKeyAuthenticator>
#include <QSslConfiguration>
#include <QSslCipher>
#include <QSslEllipticCurve>
#include <QFile>

static QByteArray readResource(QString const & path)
{
    QFile resource(path);
    resource.open(QIODevice::ReadOnly);
    return resource.readAll();
}

#include <QDebug>

DtlsSocket::DtlsSocket(QHostAddress const & address, uint16_t port) :
    mLocalCertificate(readResource(":/SecureNetwork/own.crt")),
    mCaCertificate(readResource(":/SecureNetwork/own.key")),
    mPrivateKey(readResource(":/SecureNetwork/own.key"), QSsl::KeyAlgorithm::Ec),
    mSocket(),
    mDtls(QSslSocket::SslClientMode),
    mConnected(false)
{
    mSocket.connectToHost(address, port);

    auto configuration = QSslConfiguration::defaultDtlsConfiguration();
    configuration.setCaCertificates({mCaCertificate});
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

//    QObject::connect(&mDtls, &QDtls::,
//        this, &DtlsSocket::handleHandshakeTimeout);

    mDtls.doHandshake(&mSocket);
}

void DtlsSocket::write(uint8_t const * data, size_t dataSize)
{
    if (mDtls.isConnectionEncrypted()) {
        mDtls.writeDatagramEncrypted(&mSocket, QByteArray((char const *) data, dataSize));
    }
}

void DtlsSocket::handleDatagram()
{
    QByteArray buffer(mSocket.pendingDatagramSize(), Qt::Initialization::Uninitialized);
    mSocket.read(buffer.data(), buffer.size());

    if (mDtls.isConnectionEncrypted()) {
        QByteArray const plainText = mDtls.decryptDatagram(&mSocket, buffer);
        if (mDtls.dtlsError() == QDtlsError::RemoteClosedConnectionError) {
            // TODO handle error
            return;
        }

        dataReady(buffer);
    } else {
        if (!mDtls.doHandshake(&mSocket, buffer)) {
            qDebug() << "DTLS Error" << (int) mDtls.dtlsError();
            for (auto & e : mDtls.peerVerificationErrors()){
                qDebug() << e;
            }

            mDtls.ignoreVerificationErrors(mDtls.peerVerificationErrors());
            if (!mDtls.resumeHandshake(&mSocket)) {
                qDebug() << "DTLS Resume error";
            }
        }
        if (mDtls.isConnectionEncrypted()) {
            connected(true);
        }
    }
}

void DtlsSocket::handleHandshakeTimeout()
{
    if(!mDtls.handleTimeout(&mSocket)) {
        qDebug() << "DTLS Timeout";
        // TODO handle error
    }
}
