#include "socket.h"

#include "binarystream.h"

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

    int SocketUdp::mInstCount = 0;

    SocketUdp::SocketUdp()
    {
        if(mInstCount == 0) {
            WSADATA wsa_data;
            WSAStartup(MAKEWORD(2,2), &wsa_data);
        }
        ++mInstCount;

        mSocket = socket(AF_INET, SOCK_DGRAM, 0);

    }

    SocketUdp::~SocketUdp()
    {
        closesocket(mSocket);

        --mInstCount;
        if(mInstCount == 0) {
            WSACleanup();
        }
    }

    bool SocketUdp::connect(const Address & address)
    {
        return (::connect(mSocket, address.asSockAddr(), address.size()) == 0);
    }

    bool SocketUdp::disconnect()
    {
        sockaddr_in address = {0};
        address.sin_family = AF_UNSPEC;
        return (::connect(mSocket, (sockaddr *) &address, sizeof(sockaddr_in)) == 0);
    }

    bool SocketUdp::bind(const Address & address)
    {
        return (::bind(mSocket, address.asSockAddr(), address.size()) == 0);
    }

    int SocketUdp::receive(void *buffer, int bufferSize)
    {
        return ::recv(mSocket, reinterpret_cast<char *>(buffer), bufferSize, 0);
    }

    int SocketUdp::receiveFrom(void *buffer, int bufferSize, Address & retAddress)
    {
        int asd = retAddress.size();
        return ::recvfrom(mSocket, reinterpret_cast<char *>(buffer), bufferSize, 0, retAddress.asSockAddr(), &asd);
    }

    int SocketUdp::send(const void *buffer, int bufferSize)
    {
        return ::send(mSocket, reinterpret_cast<const char *>(buffer), bufferSize, 0);
    }

    int SocketUdp::send(const BinaryStream & stream) {
        return send(stream.data(), static_cast<int>(stream.count()));
    }

    int SocketUdp::sendTo(const void *buffer, int bufferSize, Address & address)
    {
        return ::sendto(mSocket, reinterpret_cast<const char *>(buffer), bufferSize, 0, address.asSockAddr(), address.size());
    }

    bool SocketUdp::setNonBlock(bool shouldBlock)
    {
        u_long block = shouldBlock ? 1 : 0;
        return (ioctlsocket(mSocket, FIONBIO, &block) == 0);
    }

    bool SocketUdp::setReceiveTimeout(int microseconds)
    {
        DWORD tv = static_cast<DWORD>(microseconds / 1000);
        int retVal = setsockopt(mSocket,
                                SOL_SOCKET,
                                SO_RCVTIMEO,
                                reinterpret_cast<const char *>(&tv),
                                sizeof(DWORD));
        return retVal == 0;
    }

    bool SocketUdp::setBroadcast(bool enableBroadcast)
    {
        int val = enableBroadcast ? 1 : 0;
        return (setsockopt(mSocket, SOL_SOCKET, SO_BROADCAST,
                           reinterpret_cast<const char *>(&val), sizeof(int)) == 0);
    }
}
