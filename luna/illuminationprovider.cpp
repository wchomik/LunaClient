#include "illuminationprovider.h"

#include "config.h"

namespace luna {
    IlluminationProvider::IlluminationProvider(QObject * parent) :
        Provider(parent),
        mTimer(this),
        mColor(1, 1, 1, 1),
        mWhiteness(0.0)
    {
        mTimer.setInterval(20);
        connect(&mTimer, &QTimer::timeout,
                this, &IlluminationProvider::update);
    }

    void IlluminationProvider::configure(const Config & config){
        Provider::configure(config);
    }

    void IlluminationProvider::start(){
        mTimer.start();
    }

    void IlluminationProvider::stop(){
        mTimer.stop();
    }

    ColorMode IlluminationProvider::colorMode(class ColorSpace * outColorSpace)
    {
        return ColorMode::fullWhiteBalanced;
    }

    void IlluminationProvider::setUpdateRate(int rate){
        mTimer.setInterval(1000 / rate);
    }

    void IlluminationProvider::update(){
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
