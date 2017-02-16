#ifndef LUNAPROVIDER_H
#define LUNAPROVIDER_H

#include <vector>
#include <QObject>
#include "colorutils.h"
#include "colormode.h"

namespace luna {
    class LunaProvider : public QObject
    {
        Q_OBJECT
    public:
        explicit LunaProvider(QObject * parent = nullptr);
        virtual ~LunaProvider();

        virtual void configure(const struct LunaConfig & config) = 0;
        virtual ColorMode colorMode() = 0;

        std::vector<PixelStrand> & pixelStrands(){
            return mPixelStrands;
        }
        std::vector<ColorScalar> & whiteStrands(){
            return mWhiteStrands;
        }

    signals:
        void dataReady();

    public slots:
        virtual void start() = 0;
        virtual void stop() = 0;

    protected:
        std::vector<PixelStrand> mPixelStrands;
        std::vector<ColorScalar> mWhiteStrands;
    };
}

#endif // LUNAPROVIDER_H
