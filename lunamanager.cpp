#include "lunamanager.h"

#include "luna.h"
#include "lunalegacy.h"

#include "lunaprovider.h"
#include "lunailluminationprovider.h"
#include "lunaaudioprovider.h"
#include "lunascreenprovider.h"

#include "lunaconfig.h"
#include "colorspace.h"
#include "colorprocessor.h"

#include <QDebug>

namespace luna {
    LunaManager::LunaManager(QObject *parent) :
        QObject(parent),
        mWhiteBalance(1, 1, 1, 1),
        mConnectionTimer(this),
        mLuna(nullptr),
        mCurrentProviderType(LunaProviderType::illumination)
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
        QObject::disconnect(mLuna, &Luna::disconnected,
                            this, &LunaManager::onDisconnected);
        mLuna->shutdown();
    }

    void LunaManager::setWhiteBalance(const Color &color)
    {
        mWhiteBalance = color;
        updateColorMode();
    }

    void LunaManager::onDataReady()
    {
        if(mLuna->isConnected() && mActiveProvider){
            for(PixelStrand & strand : mActiveProvider->pixelStrands()){
                mColorProcessor->process(strand);
            }
            mLuna->update(mActiveProvider->pixelStrands(),
                          mActiveProvider->whiteStrands());
        }
    }

    void LunaManager::onConnected(){
        mLuna->getConfig(&mLunaConfig);
        // TODO read colorspace from LunaConfig
        mDestinationColorSpace = ColorSpace::ws2812();
        mConnectionTimer.stop();
        activateProvider();
    }

    void LunaManager::onDisconnected(){
        deactivateProvider();
        mConnectionTimer.start();
    }

    void LunaManager::activateProvider()
    {
        mActiveProvider = mProviderFactory.make(mCurrentProviderType, this);
        if(mActiveProvider){
            mActiveProvider->configure(mLunaConfig);
            QObject::connect(mActiveProvider.get(), &LunaProvider::dataReady,
                         this, &LunaManager::onDataReady);
            ColorSpace colorSpace;
            ColorMode mode = mActiveProvider->colorMode(&colorSpace);
            setColorMode(mode, colorSpace);
            mActiveProvider->start();
        }
    }

    void LunaManager::deactivateProvider()
    {
        if(mActiveProvider){
            mActiveProvider->stop();
            QObject::disconnect(mActiveProvider.get(), &LunaProvider::dataReady,
                                this, &LunaManager::onDataReady);
            mActiveProvider = std::unique_ptr<LunaProvider>();
        }
    }

    void LunaManager::updateColorMode()
    {
        switch(mCurrentColorMode){
        case ColorMode::fullWhiteBalanced:
            mColorProcessor = std::make_unique<ColorProcessorWhiteBalanced>(mWhiteBalance);
            break;
        case ColorMode::colorSpaceConversion:
            mColorProcessor = std::make_unique<ColorProcessorColorSpace>(
                mSourceColorSpace, mDestinationColorSpace, mWhiteBalance);
            break;
        case ColorMode::fullDirect:
        default:
            mColorProcessor = std::make_unique<ColorProcessorDirect>();
            break;
        }
    }

    void LunaManager::setMode(LunaProviderType type)
    {
        deactivateProvider();
        mCurrentProviderType = type;
        if(mLuna->isConnected()){
            activateProvider();
        }
    }

    void LunaManager::setColorMode(ColorMode mode, const ColorSpace & colorSpace)
    {
        mCurrentColorMode = mode;
        mSourceColorSpace = colorSpace;
        updateColorMode();
    }
}
