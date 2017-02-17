#include "lunaaudioprovider.h"

#include "lunaconfig.h"

namespace luna {
    LunaAudioProvider::LunaAudioProvider(QObject * parent) :
        LunaProvider(parent),
        mAudioCapture(this)
    {

    }

    void LunaAudioProvider::configure(const LunaConfig &config)
    {
        LunaProvider::configure(config);
        mAudioCapture.configure(2, 100.0);
    }

    ColorMode LunaAudioProvider::colorMode()
    {
        return ColorMode::nativeWhiteBalancedGamma;
    }

    void LunaAudioProvider::start()
    {
        mAudioCapture.start();
    }

    void LunaAudioProvider::stop()
    {
        mAudioCapture.stop();
    }
}
