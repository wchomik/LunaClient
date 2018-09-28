#include "hostdiscovery.h"

#include <chrono>

using namespace std::chrono_literals;

HostDiscovery::HostDiscovery() :
    mDiscoveryTimer()
{
    mSocket.bind(QHostAddress::AnyIPv4);

    QObject::connect(&mDiscoveryTimer, &QTimer::timeout,
        this, &HostDiscovery::discover);

    QObject::connect(&mSocket, &QUdpSocket::readyRead,
        this, &HostDiscovery::handleResponse);

    mDiscoveryTimer.start(1s);
    QTimer::singleShot(0, this, &HostDiscovery::discover);
}

void HostDiscovery::discover()
{
    //qDebug() << "Discovery";
    QByteArray message("Dupa blada");
    uint16_t port = 9510;

    for (auto const & interface : QNetworkInterface::allInterfaces()) {
        if (interface.flags() & QNetworkInterface::IsLoopBack) continue;
        for (auto const & entry : interface.addressEntries()) {
            auto const & address = entry.broadcast();
            if (address.isNull()) continue;
            //qDebug() << "sending to" << address.toString();
            mSocket.writeDatagram(message, address, port);
        }
    }
}

void HostDiscovery::handleResponse()
{
    //qDebug() << "got something";

    QHostAddress hostAddress;
    char data[16];
    uint16_t port;
    mSocket.readDatagram(data, 16, &hostAddress, &port);

    bool exists = false;
    for (auto const & host : mKnownHosts) {
        if (host.address == hostAddress) {
            exists = true;
            break;
        }
    }

    if (!exists) {
        mKnownHosts.emplace_back(Host{hostAddress});
        hostDiscovered(hostAddress);
    }
}
