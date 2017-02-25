#ifndef SOCKET_H
#define SOCKET_H

// fucking windows and its macros
#define NOMINMAX
#define WIN32_LEAN_AND_MEAN
/* See http://stackoverflow.com/questions/12765743/getaddrinfo-on-win32 */
#ifndef _WIN32_WINNT
    #define _WIN32_WINNT 0x0501  /* Windows XP. */
#endif
#include <winsock2.h>
#include <Ws2tcpip.h>
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
    private:
        sockaddr_in mSockAddrIn;
        sockaddr * asSockAddr(){ return reinterpret_cast<sockaddr *>(&mSockAddrIn); }
        const sockaddr * asSockAddr() const { return reinterpret_cast<const sockaddr *>(&mSockAddrIn); }
        int size() const { return sizeof(sockaddr_in); }
        friend class SocketUdp;
    public:
        friend std::ostream & operator<<(std::ostream & stream, const Address & address);
    };

    class SocketUdp
    {
    public:
        SocketUdp();
        ~SocketUdp();

        bool connect(const Address & address);
        bool disconnect();
        bool bind(const Address & address);
        int receive(void * buffer, int bufferSize);
        int receiveFrom(void * buffer, int bufferSize, Address & retAddress);
        int send(const void * buffer, int bufferSize);
        int sendTo(const void * buffer, int bufferSize, Address & address);

        bool setNonBlock(bool shouldBlock);
        bool setReceiveTimeout(int microseconds);
        bool setBroadcast(bool enableBroadcast);

    private:
        static int mInstCount;

        SOCKET mSocket;
    };
}



#endif // SOCKET_H
