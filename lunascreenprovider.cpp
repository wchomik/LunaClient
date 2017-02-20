#include "lunascreenprovider.h"

#include "lunaconfig.h"

namespace luna {

    LunaScreenProvider::LunaScreenProvider(QObject * parent) :
        LunaProvider(parent),
        mScreenCapture(this)
    {
        QObject::connect(&mScreenCapture, &graphics::ScreenCapture::dataReady,
                         this, &LunaScreenProvider::onDataReady);
    }

    void LunaScreenProvider::configure(const LunaConfig &config)
    {
        LunaProvider::configure(config);
    }

    ColorMode LunaScreenProvider::colorMode()
    {
        // TODO find a way to read system colorspace
        return ColorMode::sRgb;
    }

    void LunaScreenProvider::start()
    {
        mScreenCapture.start();
    }

    void LunaScreenProvider::stop()
    {
        mScreenCapture.stop();
    }

    void LunaScreenProvider::onDataReady()
    {
        Array2D & pixels = mScreenCapture.pixels();


    }

}
