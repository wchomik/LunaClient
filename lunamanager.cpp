#include "lunamanager.h"

#include "luna.h"
#include "lunalegacy.h"

#include "lunaprovider.h"
#include "lunailluminationprovider.h"

#include "lunaconfig.h"
#include "colorspace.h"
#include "colorprocessor.h"

namespace luna {
    LunaManager::LunaManager(QObject *parent) :
        QObject(parent),
        mConnectionTimer(this),
        mLuna(nullptr),
        mProvider(nullptr),
        mColorProcessor(nullptr)
    {
        mLuna = new LunaLegacy(this);

        mConnectionTimer.setInterval(100);

        QObject::connect(&mConnectionTimer, &QTimer::timeout, mLuna, &Luna::connect);
        QObject::connect(mLuna, &Luna::connected, this, &LunaManager::onConnected);
        QObject::connect(mLuna, &Luna::disconnected,this, &LunaManager::onDisconnected);

        mConnectionTimer.start();
    }

    LunaManager::~LunaManager()
    {
        if(mColorProcessor) delete mColorProcessor;
    }

    void LunaManager::onShutdown()
    {
        QObject::disconnect(mLuna, &Luna::disconnected,this, &LunaManager::onDisconnected);
        mLuna->shutdown();
    }

    void LunaManager::onDataReady()
    {
        if(mLuna->isConnected()){
            for(PixelStrand & strand : mProvider->pixelStrands()){
                mColorProcessor->process(strand);
            }
            mLuna->update(mProvider->pixelStrands(),
                          mProvider->whiteStrands());
        }
    }

    void LunaManager::onConnected(){
        mConnectionTimer.stop();

        LunaIlluminationProvider * illum = new LunaIlluminationProvider(this);

        illum->configure(mLuna->config());
        illum->setUpdateRate(10);
        illum->mColor = Color(0, 1, 0, 0);
        illum->mWhiteness = 0.0f;

        setProvider(illum);
    }

    void LunaManager::onDisconnected(){
        mConnectionTimer.start();
    }

    void LunaManager::setProvider(LunaProvider * provider)
    {
        if(mProvider){
            mProvider->stop();
            QObject::disconnect(mProvider, &LunaProvider::dataReady,
                                this, &LunaManager::onDataReady);
        }
        mProvider = provider;
        if(provider){
            QObject::connect(mProvider, &LunaProvider::dataReady,
                         this, &LunaManager::onDataReady);
            mProvider->start();
            setColorMode(mProvider->colorMode());
        }
    }

    void LunaManager::setColorMode(ColorMode mode)
    {
        if(mColorProcessor){
            delete mColorProcessor;
        }
        // TODO read gamma from config
        // TODO read white balance from config
        // TODO read luna colorspace from config
        ColorScalar mGamma = 2.2;
        Color mWhiteBalance(1, 1, 1, 1);
        ColorSpace mColorSpace = ColorSpace::ws2812();
        switch(mode){
        case ColorMode::nativeDirectGamma:
            mColorProcessor = new ColorProcessorDirectGamma(mGamma);
            break;
        case ColorMode::nativeWhiteBalanced:
            mColorProcessor = new ColorProcessorWhiteBalanced(mWhiteBalance);
            break;
        case ColorMode::nativeWhiteBalancedGamma:
            mColorProcessor = new ColorProcessorWhiteBalancedGamma(mWhiteBalance, mGamma);
            break;
        case ColorMode::rec2020:
            mColorProcessor = new ColorProcessorColorSpace(
                ColorSpace::rec2020(), mColorSpace, mWhiteBalance);
            break;
        case ColorMode::sRgb:
            mColorProcessor = new ColorProcessorColorSpace(
                ColorSpace::sRGB(), mColorSpace, mWhiteBalance);
            break;
        case ColorMode::nativeDirect:
        default:
            mColorProcessor = new ColorProcessorDirect();
            break;
        }
    }
}
