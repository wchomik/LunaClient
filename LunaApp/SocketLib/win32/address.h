#ifndef ADDRESS_H
#define ADDRESS_H


#include <WinSock2.h>

#include <cstdint>
#include <ostream>

namespace net {
    class Address{
    public:
        enum SpecialAddress{
            ANY,
            BROADCAST,
            LOOPBACK,
        };
        Address(){}
        Address(uint8_t a0, uint8_t a1, uint8_t a2, uint8_t a3, uint16_t port);
        Address(SpecialAddress special, uint16_t port);

        void setPort(uint16_t port);
    private:
        sockaddr_in mSockAddrIn;
        sockaddr * asSockAddr(){ return reinterpret_cast<sockaddr *>(&mSockAddrIn); }
        const sockaddr * asSockAddr() const { return reinterpret_cast<const sockaddr *>(&mSockAddrIn); }
        int size() const { return sizeof(sockaddr_in); }
        friend class SocketUdp;
    public:
        friend std::ostream & operator<<(std::ostream & stream, const Address & address);

        bool operator==(const Address & other) const;
        bool operator!=(const Address & other) const { return !((*this) == other); }
    };
}

#endif // ADDRESS_H
