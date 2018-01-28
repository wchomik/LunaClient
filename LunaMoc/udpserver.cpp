#include "udpserver.h"

#include <QtNetwork/QNetworkDatagram>
#include <QQmlEngine>
#include "pixelprovider.h"

UdpServer::UdpServer(QObject *parent) :
    QObject(parent),
    mPort(0),
    mIsConnected(false)
{
    mLeftPixels = new PixelProvider(120);
    QQmlEngine::setObjectOwnership(mLeftPixels, QQmlEngine::CppOwnership);
    mRightPixels = new PixelProvider(120);
    QQmlEngine::setObjectOwnership(mRightPixels, QQmlEngine::CppOwnership);

    mSocket = new QUdpSocket(this);
    QObject::connect(mSocket, &QUdpSocket::readyRead, this, &UdpServer::readDatagrams);
    mTimer = new QTimer(this);
    mTimer->setInterval(5000);
    QObject::connect(mTimer, &QTimer::timeout, this, &UdpServer::disconnectFromClient);
}

UdpServer::~UdpServer()
{
}

void UdpServer::listenOnPort(int port)
{
    qDebug() << "Listening on port " << port;
    mPort = port;
    disconnectFromClient();

}

PixelProvider *UdpServer::leftPixels()
{
    return mLeftPixels;
}

PixelProvider *UdpServer::rightPixels()
{
    return mRightPixels;
}

void UdpServer::readDatagrams()
{
    while (mSocket->hasPendingDatagrams()) {
        QNetworkDatagram datagram = mSocket->receiveDatagram();
        processDatagram(datagram);
    }
}

void UdpServer::processDatagram(QNetworkDatagram &datagram)
{
    mTimer->start();
    int command = datagram.data()[0];

    if (!mIsConnected) {
        connectToClient(datagram.senderAddress(), datagram.senderPort());
    }

    qDebug() << datagram.data().size() << " bytes. cmb " << (int)datagram.data()[0];

    switch(command) {
    case 99:
        disconnectFromClient();
        break;
    case 101:
        updatePixels(datagram.data());
        break;
    default:
        break;
    }
}

void UdpServer::connectToClient(const QHostAddress &address, uint16_t port)
{
    qDebug() << "Connecting to client";
    mIsConnected = true;
    //mSocket->close();

    QNetworkDatagram msg;
    msg.setData(QString("Hello").toUtf8());
    msg.setDestination(address, port);
    mSocket->writeDatagram(msg);

    //mSocket->bind(address, port);
    mTimer->start();
}

void UdpServer::disconnectFromClient()
{
    qDebug() << "Disconnecting from client.";

    mIsConnected = false;
    mSocket->close();
    mSocket->bind(QHostAddress::AnyIPv4, mPort);
    mTimer->stop();
}

void UdpServer::updatePixels(const QByteArray & data)
{
    int i = 1;

    if (data[i] == 61) {
        i += 5;
        updateStrand(mLeftPixels, (uint8_t *) data.data() + i);
        i += 360;
        updateStrand(mRightPixels, (uint8_t *) data.data() + i);
    }
}

void UdpServer::updateStrand(PixelProvider *strand, const uint8_t *data)
{
    for (int i = 0; i < 120; ++i) {
        uint8_t r, g, b;
        r = data[i * 3 + 0];
        g = data[i * 3 + 1];
        b = data[i * 3 + 2];
        QColor color(r, g, b, 255);
        strand->setPixel(i, color);
    }
}
