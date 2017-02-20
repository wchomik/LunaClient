#ifndef LUNASCREENPROVIDER_H
#define LUNASCREENPROVIDER_H

#include "lunaprovider.h"
#include "screencapture.h"

namespace luna {
    class LunaScreenProvider : public LunaProvider
    {
    public:
        explicit LunaScreenProvider(QObject * parent = nullptr);

        void configure(const struct LunaConfig & config) override;
        ColorMode colorMode() override;

        void start() override;
        void stop() override;
    private slots:
        void onDataReady();
    private:
        graphics::ScreenCapture mScreenCapture;
    };
}

#endif // LUNASCREENPROVIDER_H
