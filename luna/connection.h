#ifndef LUNALEGACY_H
#define LUNALEGACY_H

#include <memory>
#include <string>
#include <chrono>
#include "binarystream.h"
#include "socket.h"
#include "colorutils.h"
#include "event.h"

namespace luna {
    class Host {
    public:
        Host();
        Host(const std::string & name) : mName(name) {}

        const std::string & name(){ return mName; }
    private:
        std::string mName;
        net::Address mAddress;
        friend class Connection;
    };

    class Connection
    {
    public:
        Connection();
        ~Connection();

        bool isConnected();
        void sendPixels(const std::vector<PixelStrand> & pixelStrands,
            const std::vector<ColorScalar> & whiteStrands);

        void update();
        std::vector<Host> getHosts();
        void getConfig(struct Config & config);
        void connect(const Host & host);
        void disconnect();

        Event<void()> onHostsChanged;
        Event<void()> onConnected;
        Event<void()> onDisconnected;
    private:
        enum {
            PIXEL_COUNT = 120,
            PORT = 1234,
            BUFFER_SIZE  = 6 + PIXEL_COUNT * 6,
        };
        bool mIsConnected;
        net::SocketUdp mSocket;
        BinaryStream<BUFFER_SIZE> mBuffer;
        std::vector<Host> mHostList;
        std::chrono::steady_clock::time_point mLastKeepAlive;
        void send();
    };
}
#endif // LUNALEGACY_H
