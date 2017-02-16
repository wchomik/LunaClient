#ifndef LUNA_H
#define LUNA_H

#include <QObject>
#include "colorutils.h"
#include "lunaconfig.h"

namespace luna {
    class Luna : public QObject
    {
        Q_OBJECT
    public:
        explicit Luna(QObject * parent = nullptr);
        virtual ~Luna();
        virtual bool isConnected() = 0;

        virtual void connect() = 0;
        virtual void disconnect() = 0;
        virtual void update(const std::vector<PixelStrand> & pixelStrands,
                            const std::vector<ColorScalar> & whiteStrands) = 0;
        virtual void shutdown() = 0;

        const LunaConfig & config(){
            return mConfig;
        }

    signals:
        void connected();
        void disconnected();

    protected:
        LunaConfig mConfig;
    };
}
#endif // LUNA_H
