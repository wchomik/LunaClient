#ifndef LUNALEGACY_H
#define LUNALEGACY_H

#include "connection.h"
#include "binarystream.h"
#include "socket.h"

namespace luna {
    class HostLegacy : public Host {
    private:
        net::Address mAddress;
        friend class ConnectionLegacy;
    };

    class ConnectionLegacy : public Connection
    {
    public:
        ConnectionLegacy();
        virtual ~ConnectionLegacy();

        bool isConnected() override;


        void sendPixels(const std::vector<PixelStrand> & pixelStrands,
                    const std::vector<ColorScalar> & whiteStrands) override;

        void update() override;
        const std::vector<std::shared_ptr<Host>> & getHosts() override;
        void getConfig(struct Config * config) override;
        void connect(const Host * host) override;
        void disconnect() override;
    private:
        enum {
            PIXEL_COUNT = 120,
            PORT = 1234,
            BUFFER_SIZE  = 6 + PIXEL_COUNT * 6,
        };
        bool mIsConnected;
        net::SocketUdp mSocket;
        BinaryStream<BUFFER_SIZE> mBuffer;
        std::vector<std::shared_ptr<Host>> mHostList;
        void send();
    };
}
#endif // LUNALEGACY_H
