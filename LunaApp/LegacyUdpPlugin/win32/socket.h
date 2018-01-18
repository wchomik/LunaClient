#ifndef SOCKET_H
#define SOCKET_H

#include <WinSock2.h>
#include <cstdint>

#include <ostream>

class BinaryStream;

namespace net {
    class Address;

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
        int send(const BinaryStream & stream);
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
