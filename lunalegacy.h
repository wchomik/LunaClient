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

        bool isConnected() override;
        QAbstractListModel * devices() override;

        void connect() override;
        void disconnect() override;
        void update(const std::vector<PixelStrand> & pixelStrands,
                    const std::vector<ColorScalar> & whiteStrands) override;
        void shutdown() override;
        void discover() override;

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

        // Luna interface
    };
}
#endif // LUNALEGACY_H
