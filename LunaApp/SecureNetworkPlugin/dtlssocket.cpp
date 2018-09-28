#include "dtlssocket.h"

#include <QSslPreSharedKeyAuthenticator>
#include <QSslConfiguration>
#include <QSslCipher>

#include <QDebug>

DtlsSocket::DtlsSocket(QHostAddress const & address, uint16_t port, QByteArray const & sharedKey) :
    mSocket(),
    mDtls(QSslSocket::SslClientMode),
    mConnected(false)
{
    mSocket.connectToHost(address, port);

    auto configuration = QSslConfiguration::defaultDtlsConfiguration();
    configuration.setPeerVerifyMode(QSslSocket::VerifyNone);
    mDtls.setDtlsConfiguration(configuration);
    mDtls.setPeer(address, port);

    QObject::connect(&mDtls, &QDtls::pskRequired,
        [sharedKey](QSslPreSharedKeyAuthenticator *authenticator){
            qDebug() << "DTLS PSK";
            QByteArray identity("Luna", 4);
            authenticator->setIdentity(identity);
            authenticator->setPreSharedKey(sharedKey);
        });

    QObject::connect(&mDtls, &QDtls::handshakeTimeout,
        this, &DtlsSocket::handleHandshakeTimeout);

    QObject::connect(&mSocket, &QUdpSocket::readyRead,
        this, &DtlsSocket::handleDatagram);

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
            qDebug() << "DTLS Error";
            // TODO handle error
        } else if (mDtls.isConnectionEncrypted()) {
            qDebug() << "DTLS Connected";
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
