#include "lunailluminationprovider.h"

#include "lunaconfig.h"

namespace luna {
    LunaIlluminationProvider::LunaIlluminationProvider(QObject * parent) :
        LunaProvider(parent),
        mTimer(this),
        mColor(1, 1, 1, 1),
        mWhiteness(0.0)
    {
        mTimer.setInterval(20);
        connect(&mTimer, &QTimer::timeout,
                this, &LunaIlluminationProvider::update);
    }

    void LunaIlluminationProvider::configure(const LunaConfig & config){
        LunaProvider::configure(config);
    }

    void LunaIlluminationProvider::start(){
        mTimer.start();
    }

    void LunaIlluminationProvider::stop(){
        mTimer.stop();
    }

    ColorMode LunaIlluminationProvider::colorMode(class ColorSpace * outColorSpace)
    {
        return ColorMode::fullWhiteBalanced;
    }

    void LunaIlluminationProvider::setUpdateRate(int rate){
        mTimer.setInterval(1000 / rate);
    }

    void LunaIlluminationProvider::update(){
        for(PixelStrand & strand : mPixelStrands){
            for(Color & pixel : strand){
                pixel = mColor;
            }
        }
        for(ColorScalar & strand : mWhiteStrands){
            strand = mWhiteness;
        }
        emit dataReady();
    }


}
