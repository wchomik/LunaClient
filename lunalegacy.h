#ifndef LUNALEGACY_H
#define LUNALEGACY_H

#include <QUdpSocket>
#include "luna.h"
#include "binarystream.h"

namespace luna {
    class LunaLegacy : public Luna
    {
    public:
        explicit LunaLegacy(QObject * parent = nullptr);
        virtual ~LunaLegacy();

        virtual bool isConnected() override;
        virtual void connect() override;
        virtual void disconnect() override;
        virtual void update(const std::vector<PixelStrand> & pixelStrands,
                            const std::vector<ColorScalar> & whiteStrands) override;
        virtual void shutdown() override;
    protected slots:
        void datagramReceived();
    private:
        enum {
            pixelCount = 120,
            port = 1234,
            bufferSize = 6 + pixelCount * 6,
        };
        bool mIsConnected;
        QUdpSocket mSocket;
        BinaryStream<bufferSize> mBuffer;

        static const char * helloMessage;

        void send();
        void makeConfig();
    };
}
#endif // LUNALEGACY_H
