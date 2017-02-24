#include "manager.h"

#include <chrono>

#include "connection.h"
#include "connectionlegacy.h"

#include "providerfactory.h"

#include "config.h"
#include "colorspace.h"
#include "colorprocessor.h"
#include <iostream>
namespace ch = std::chrono;

namespace luna {
    Manager::Manager() :
        mWhiteBalance(1, 1, 1, 1),
        mLuna(std::make_unique<ConnectionLegacy>()),
        mCurrentProviderType(ProviderType::illumination),
        mShouldRun(true),
        mThread([this](){ threadFunc(); })
    {}

    Manager::~Manager()
    {
        mShouldRun = false;
        mThread.join();
    }

    void Manager::setWhiteBalance(const Color &color)
    {
        mWhiteBalance = color;
        updateColorMode();
    }

    void Manager::threadFunc()
    {
        ch::steady_clock::time_point nextPeriod =
            ch::steady_clock::now() + ch::milliseconds(10);
        while(mShouldRun){
            if(mLuna->isConnected()){
                if(mActiveProvider->getData(mPixelStrands, mWhiteStands)){
                    for(PixelStrand & strand : mPixelStrands){
                        mColorProcessor->process(strand);
                    }
                    mLuna->update(mPixelStrands,mWhiteStands);
                }
            }else{
                if(mLuna->connect()){
                    mLuna->getConfig(&mLunaConfig);
                    mPixelStrands.clear();
                    mWhiteStands.clear();
                    for(auto & conf : mLunaConfig.pixelStrands){
                        mPixelStrands.emplace_back(conf.count);
                    }
                    for(auto & conf : mLunaConfig.whiteStrands){
                        mWhiteStands.emplace_back(0);
                    }
                    // TODO read colorspace from LunaConfig
                    mDestinationColorSpace = ColorSpace::ws2812();
                    updateColorMode();
                    activateProvider();
                }
            }
            ch::duration<double, std::milli> diff;
            while((diff = ch::steady_clock::now() - nextPeriod).count() < -1){
                std::this_thread::sleep_until(nextPeriod);
            }
            nextPeriod += ch::milliseconds(10);
        }
    }

    void Manager::activateProvider()
    {
        mActiveProvider = mProviderFactory.make(mCurrentProviderType);
        if(mActiveProvider){
            mActiveProvider->configure(mLunaConfig);
            mCurrentColorMode = mActiveProvider->colorMode(&mSourceColorSpace);
            updateColorMode();
        }
    }

    void Manager::deactivateProvider()
    {
        if(mActiveProvider){
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

}
