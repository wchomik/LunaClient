#include "manager.h"

#include "connection.h"
#include "connectionlegacy.h"

#include "provider.h"
#include "illuminationprovider.h"
#include "audioprovider.h"
#include "screenprovider.h"

#include "config.h"
#include "colorspace.h"
#include "colorprocessor.h"

#include <QDebug>

namespace luna {
    Manager::Manager(QObject *parent) :
        QObject(parent),
        mWhiteBalance(1, 1, 1, 1),
        mConnectionTimer(this),
        mLuna(nullptr),
        mCurrentProviderType(ProviderType::illumination)
    {
        mLuna = new ConnectionLegacy(this);

        mConnectionTimer.setInterval(100);

        QObject::connect(&mConnectionTimer, &QTimer::timeout, mLuna, &Connection::connect);
        QObject::connect(mLuna, &Connection::connected, this, &Manager::onConnected);
        QObject::connect(mLuna, &Connection::disconnected,this, &Manager::onDisconnected);

        mConnectionTimer.start();
    }

    Manager::~Manager()
    {
        QObject::disconnect(mLuna, &Connection::disconnected,
                            this, &Manager::onDisconnected);
        mLuna->shutdown();
    }

    void Manager::setWhiteBalance(const Color &color)
    {
        mWhiteBalance = color;
        updateColorMode();
    }

    void Manager::onDataReady()
    {
        if(mLuna->isConnected() && mActiveProvider){
            for(PixelStrand & strand : mActiveProvider->pixelStrands()){
                mColorProcessor->process(strand);
            }
            mLuna->update(mActiveProvider->pixelStrands(),
                          mActiveProvider->whiteStrands());
        }
    }

    void Manager::onConnected(){
        mLuna->getConfig(&mLunaConfig);
        // TODO read colorspace from LunaConfig
        mDestinationColorSpace = ColorSpace::ws2812();
        mConnectionTimer.stop();
        activateProvider();
    }

    void Manager::onDisconnected(){
        deactivateProvider();
        mConnectionTimer.start();
    }

    void Manager::activateProvider()
    {
        mActiveProvider = mProviderFactory.make(mCurrentProviderType, this);
        if(mActiveProvider){
            mActiveProvider->configure(mLunaConfig);
            QObject::connect(mActiveProvider.get(), &Provider::dataReady,
                         this, &Manager::onDataReady);
            ColorSpace colorSpace;
            ColorMode mode = mActiveProvider->colorMode(&colorSpace);
            setColorMode(mode, colorSpace);
            mActiveProvider->start();
        }
    }

    void Manager::deactivateProvider()
    {
        if(mActiveProvider){
            mActiveProvider->stop();
            QObject::disconnect(mActiveProvider.get(), &Provider::dataReady,
                                this, &Manager::onDataReady);
            mActiveProvider = std::unique_ptr<Provider>();
        }
    }

    void Manager::updateColorMode()
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

    void Manager::setMode(ProviderType type)
    {
        deactivateProvider();
        mCurrentProviderType = type;
        if(mLuna->isConnected()){
            activateProvider();
        }
    }

    void Manager::setColorMode(ColorMode mode, const ColorSpace & colorSpace)
    {
        mCurrentColorMode = mode;
        mSourceColorSpace = colorSpace;
        updateColorMode();
    }
}
