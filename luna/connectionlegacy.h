#ifndef LUNALEGACY_H
#define LUNALEGACY_H

#include "connection.h"
#include "binarystream.h"
#include "socket.h"

namespace luna {
    class ConnectionLegacy : public Connection
    {
    public:
        ConnectionLegacy();
        virtual ~ConnectionLegacy();

        bool isConnected() override;

        bool connect() override;
        void disconnect() override;
        void update(const std::vector<PixelStrand> & pixelStrands,
                    const std::vector<ColorScalar> & whiteStrands) override;
        void getConfig(struct Config * config) override;

    private:
        enum {
            PIXEL_COUNT = 120,
            PORT = 1234,
            BUFFER_SIZE  = 6 + PIXEL_COUNT * 6,
        };
        bool mIsConnected;
        sock_t mSocket;
        BinaryStream<BUFFER_SIZE> mBuffer;

        static const char * helloMessage;

        void send();
    };
}
#endif // LUNALEGACY_H
