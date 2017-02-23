#ifndef LUNAILLUMINATIONPROVIDER_H
#define LUNAILLUMINATIONPROVIDER_H

#include <QTimer>
#include "provider.h"

namespace luna {
    class IlluminationProvider : public Provider
    {
    public:
        explicit IlluminationProvider(QObject * parent = nullptr);

        void configure(const struct Config & config) override;
        void start() override;
        void stop() override;
        ColorMode colorMode(class ColorSpace * outColorSpace) override;

        void setUpdateRate(int rate);
        Color mColor;
        ColorScalar mWhiteness;
    private:
        QTimer mTimer;

        void update();
    };
}

#endif // LUNAILLUMINATIONPROVIDER_H
