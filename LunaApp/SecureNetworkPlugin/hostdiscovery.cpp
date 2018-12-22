#include "hostdiscovery.h"

#include <QNetworkInterface>

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

    mDiscoveryTimer.start(5s);
    QTimer::singleShot(0, this, &HostDiscovery::discover);
}

void HostDiscovery::discover()
{
    QByteArray message("Dupa blada");
    uint16_t port = 9510;

    for (auto const & interface : QNetworkInterface::allInterfaces()) {
        if (interface.flags() & QNetworkInterface::IsLoopBack) continue;
        for (auto const & entry : interface.addressEntries()) {
            auto const & address = entry.broadcast();
            if (address.isNull()) continue;
            mSocket.writeDatagram(message, address, port);
        }
    }
}

void HostDiscovery::handleResponse()
{
    QHostAddress hostAddress;
    char data[1024];
    uint16_t port;
    auto size = mSocket.readDatagram(data, 1024, &hostAddress, &port);

    using namespace luna::proto;

    auto discovery = GetDiscovery(data);

    hostDiscovered(hostAddress, discovery);
}
