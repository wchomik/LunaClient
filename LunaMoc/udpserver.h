#ifndef UDPSERVER_H
#define UDPSERVER_H

#include <QObject>
#include <QUdpSocket>
#include <QTimer>

class PixelProvider;

class UdpServer : public QObject
{
    Q_OBJECT
public:
    explicit UdpServer(QObject *parent = nullptr);
    ~UdpServer();

    Q_INVOKABLE void listenOnPort(int port);
    Q_INVOKABLE PixelProvider * leftPixels();
    Q_INVOKABLE PixelProvider * rightPixels();

signals:


private slots:
    void readDatagrams();
    void disconnectFromClient();

private:
    void processDatagram(QNetworkDatagram & datagram);
    void connectToClient(const QHostAddress & address, uint16_t port);
    void updatePixels(const QByteArray & data);

    static void updateStrand(PixelProvider * strand, const uint8_t * data);

    bool mIsConnected;
    PixelProvider * mLeftPixels;
    PixelProvider * mRightPixels;
    uint16_t mPort;
    QUdpSocket * mSocket;
    QTimer * mTimer;
};

#endif // UDPSERVER_H
