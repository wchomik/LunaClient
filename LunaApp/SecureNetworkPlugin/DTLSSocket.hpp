#pragma once

#include <QUdpSocket>
#include <QDtls>
#include <QHostAddress>
#include <QByteArray>
#include <QObject>
#include <QSslCertificate>
#include <QSslKey>

class DtlsSocket : public QObject
{
    Q_OBJECT
public:
    DtlsSocket(QHostAddress const & address, uint16_t port);
    ~DtlsSocket() override;
    void write(std::byte const * data, size_t dataSize);
signals:
    void dataReady(QByteArray data);
    void connected(bool value);
private slots:
    void handleDatagram();
    void handleHandshakeTimeout();
private:
    using StepFunction = void(DtlsSocket::*)(QByteArray const & buffer);

    void doHandshake(QByteArray const & buffer);
    void readDatagram(QByteArray const & buffer);

    StepFunction mStep;
    QSslCertificate mLocalCertificate;
    QSslCertificate mCaCertificate;
    QSslKey mPrivateKey;

    QUdpSocket mSocket;
    QDtls mDtls;
    bool mConnected;
    unsigned mTimeoutCount;
};
