#ifndef LUNAILLUMINATIONPROVIDER_H
#define LUNAILLUMINATIONPROVIDER_H

#include <QTimer>
#include "lunaprovider.h"

namespace luna {
    class LunaIlluminationProvider : public LunaProvider
    {
    public:
        explicit LunaIlluminationProvider(QObject * parent = nullptr);

        void configure(const struct LunaConfig & config) override;
        void start() override;
        void stop() override;

        void setUpdateRate(int rate);
        Color mColor;
        ColorScalar mWhiteness;
    private:
        QTimer mTimer;

        void update();
    };
}

#endif // LUNAILLUMINATIONPROVIDER_H
