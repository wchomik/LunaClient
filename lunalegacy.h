#ifndef LUNALEGACY_H
#define LUNALEGACY_H

#include <QUdpSocket>
#include <QTimer>
#include "luna.h"
#include "binarystream.h"

namespace luna {
    class LunaLegacy : public Luna
    {
    public:
        explicit LunaLegacy(QObject * parent = nullptr);
        virtual ~LunaLegacy();

        bool isConnected() override;

        void connect() override;
        void disconnect() override;
        void update(const std::vector<PixelStrand> & pixelStrands,
                    const std::vector<ColorScalar> & whiteStrands) override;
        void shutdown() override;
        void getConfig(struct LunaConfig * config) override;

    protected slots:
        void datagramReceived();
        void keepAliveTimeout();
    private:
        enum {
            pixelCount = 120,
            port = 1234,
            bufferSize = 6 + pixelCount * 6,
        };
        bool mIsConnected;
        QUdpSocket mSocket;
        QTimer mKeepAliveTimer;
        BinaryStream<bufferSize> mBuffer;

        static const char * helloMessage;

        void send();
    };
}
#endif // LUNALEGACY_H
