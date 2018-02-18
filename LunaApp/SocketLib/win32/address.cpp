#include "address.h"

namespace net {
    Address::Address(uint8_t a0, uint8_t a1, uint8_t a2, uint8_t a3, uint16_t port)
    {
        mSockAddrIn.sin_family = AF_INET;
        mSockAddrIn.sin_port = htons(port);
        mSockAddrIn.sin_addr.s_addr = htonl(a3 | (a2 << 8) | (a1 << 16) | (a0 << 24));
    }

    Address::Address(Address::SpecialAddress special, uint16_t port)
    {
        mSockAddrIn.sin_family = AF_INET;
        mSockAddrIn.sin_port = htons(port);
        uint32_t addr;
        switch(special){
        case ANY:
            addr = INADDR_ANY;
            break;
        case BROADCAST:
            addr = INADDR_BROADCAST;
            break;
        case LOOPBACK:
            addr = INADDR_LOOPBACK;
            break;
        default:
            addr = INADDR_NONE;
        }
        mSockAddrIn.sin_addr.s_addr = htonl (addr);
    }

    void Address::setPort(uint16_t port) {
        mSockAddrIn.sin_port = htons(port);
    }

    bool Address::operator==(const Address & other) const {
        return (0 == memcmp(&mSockAddrIn, &(other.mSockAddrIn), sizeof(sockaddr_in)));
    }

    std::ostream & net::operator<<(std::ostream & stream, const Address & address)
    {
        return stream << inet_ntoa(address.mSockAddrIn.sin_addr);
    }
}
