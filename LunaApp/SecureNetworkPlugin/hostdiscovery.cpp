#include "hostdiscovery.h"

HostDiscovery::HostDiscovery(HostDiscovery::callback_t &&callback, std::chrono::steady_clock::duration interval) :
    mDiscoveryInterval(interval),
    mOnHostDiscovered(callback)
{
    mInterfaces = net::NetworkInterface::list();
    net::Address addr(0, 0, 0, 0, 0);
    mSocket.bind(addr);
    mSocket.setNonBlock(true);

    mNextDiscovery = std::chrono::steady_clock::now();
}

void HostDiscovery::discover()
{
    bool shouldDiscover = std::chrono::steady_clock::now() >= mNextDiscovery;

    if (shouldDiscover) {
        for (auto & interface : mInterfaces) {
            auto addr = interface.broadcast();
            addr.setPort(9510);
            char msg[] = "Dupa blada";
            mSocket.sendTo(msg, sizeof(msg), addr);
        }
        mNextDiscovery = std::chrono::steady_clock::now() + mDiscoveryInterval;
    }

    char buffer[1024];
    do {
        net::Address from;
        auto bufferSize = mSocket.receiveFrom(buffer, sizeof(buffer), from);
        if (bufferSize >= 0) {
            mOnHostDiscovered(from);
        } else {
            break;
        }
    } while (true);
}
