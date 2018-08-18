#ifndef HOSTDISCOVERY_H
#define HOSTDISCOVERY_H

#include <functional>
#include <chrono>

#include <address.h>
#include <networkinterface.h>
#include <socket.h>

class HostDiscovery
{
public:
    using callback_t = std::function<void(const net::Address &)>;
    HostDiscovery(callback_t && callback, std::chrono::steady_clock::duration interval);
    void discover();
private:
    std::vector<net::NetworkInterface> mInterfaces;
    net::SocketUdp mSocket;
    uint16_t mPort;
    std::chrono::steady_clock::duration mDiscoveryInterval;
    std::chrono::steady_clock::time_point mNextDiscovery;
    callback_t mOnHostDiscovered;
};

#endif // HOSTDISCOVERY_H
