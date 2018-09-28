#ifndef DTLSSOCKET_H
#define DTLSSOCKET_H

#include <QUdpSocket>
#include <QDtls>
#include <QHostAddress>
#include <QByteArray>
#include <QObject>

class DtlsSocket : public QObject
{
    Q_OBJECT
public:
    DtlsSocket(QHostAddress const & address, uint16_t port, QByteArray const & sharedKey);
    void write(uint8_t const * data, size_t dataSize);
signals:
    void dataReady(QByteArray data);
private slots:
    void handleDatagram();
    void handleHandshakeTimeout();
private:
    QUdpSocket mSocket;
    QDtls mDtls;
    bool mConnected;
};

#endif // DTLSSOCKET_H
