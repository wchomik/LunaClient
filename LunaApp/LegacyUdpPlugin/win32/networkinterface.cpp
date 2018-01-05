#include "networkinterface.h"

#include <memory>


#include <WS2tcpip.h>
#include <iphlpapi.h>

namespace net {
    std::vector<NetworkInterface> NetworkInterface::list() {
        std::vector<NetworkInterface> ret;

        unsigned long bufferSize = 16 * sizeof(IP_ADAPTER_ADDRESSES);
        auto buffer = std::make_unique<char[]>(bufferSize);
        auto error = GetAdaptersAddresses(AF_INET, 0, NULL,
            reinterpret_cast<IP_ADAPTER_ADDRESSES *>(buffer.get()), &bufferSize);

        if (NO_ERROR == error) {
            auto adapter = reinterpret_cast<const IP_ADAPTER_ADDRESSES *>(buffer.get());
            do {
                auto unicastAddress = adapter->FirstUnicastAddress;
                while (nullptr != unicastAddress) {
                    auto socketAddress = unicastAddress->Address.lpSockaddr;
                    if (AF_INET == socketAddress->sa_family) {
                        auto maskLength = unicastAddress->OnLinkPrefixLength;
                        ULONG mask;
                        ConvertLengthToIpv4Mask(maskLength, &mask);
                        mask = ~mask;
                        auto sockaddrin = reinterpret_cast<sockaddr_in*>(socketAddress);
                        sockaddrin->sin_addr.S_un.S_addr |= mask;
                        auto netAddress = reinterpret_cast<net::Address*>(socketAddress);

                        NetworkInterface interface;
                        interface.m_broadcast = *netAddress;
                        ret.push_back(interface);
                    }
                    unicastAddress = unicastAddress->Next;
                }
                adapter = adapter->Next;
            } while (adapter != nullptr);
        }
        return ret;
    }
}
