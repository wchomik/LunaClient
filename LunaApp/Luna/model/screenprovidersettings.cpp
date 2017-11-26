#include "screenprovidersettings.h"

namespace model {

    ScreenProviderSettings::ScreenProviderSettings(QObject *parent) :
        ProviderSettings(parent),
        mProvider(nullptr)
    {}

    ScreenProviderSettings::~ScreenProviderSettings()
    {
        mSettings->setValue("screen/depth", mDepth);
        mSettings->setValue("screen/brightness", mBrightness);
        mSettings->setValue("screen/gamma", mGamma);
    }

    void ScreenProviderSettings::setDepth(const qreal value)
    {
        if(value != mDepth){
            mDepth = value;
            applyDepth();
            depthChanged();
        }
    }

    void ScreenProviderSettings::setBrightness(const qreal value)
    {
        if(value != mBrightness){
            mBrightness = value;
            applyBrightness();
            brightnessChanged();
        }
    }

    void ScreenProviderSettings::setGamma(const qreal value)
    {
        if(value != mGamma){
            mGamma = value;
            applyGamma();
            gammaChanged();
        }
    }

    void ScreenProviderSettings::applyDepth()
    {
        if(mProvider){
            mProvider->setDepth(std::lround(mDepth));
        }
    }

    void ScreenProviderSettings::applyBrightness()
    {
        if(mProvider){
            mProvider->setBrightness(static_cast<float>(mBrightness));
        }
    }

    void ScreenProviderSettings::applyGamma()
    {
        if(mProvider){
            mProvider->setGamma(mGamma * 2);
        }
    }

    void ScreenProviderSettings::setProvider(luna::Provider *provider)
    {
        mProvider = dynamic_cast<luna::ScreenProvider *>(provider);
        applyDepth();
        applyBrightness();
        applyGamma();
    }

    void ScreenProviderSettings::setSettings(QSettings *settings)
    {
        ProviderSettings::setSettings(settings);
        mDepth = mSettings->value("screen/depth", (qreal)5).toReal();
        mBrightness = mSettings->value("screen/brightness", (qreal)1).toReal();
        mGamma = mSettings->value("screen/gamma", (qreal)0.5).toReal();
        applyDepth();
        applyBrightness();
        applyGamma();
    }
}


