#include "screenprovidersettings.h"

namespace model {

    ScreenProviderSettings::ScreenProviderSettings(QObject *parent) :
        ProviderSettings(parent),
        mProvider(nullptr)
    {}

    ScreenProviderSettings::~ScreenProviderSettings()
    {
        mSettings->setValue("screen/bottom", mBottom);
        mSettings->setValue("screen/top", mTop);
        mSettings->setValue("screen/left", mLeft);
        mSettings->setValue("screen/right", mRight);
        mSettings->setValue("screen/depth", mDepth);
    }

    void ScreenProviderSettings::setTop(const qreal value)
    {
        if(value != mTop){
            mTop = value;
            applyBounds();
            topChanged();
        }
    }

    void ScreenProviderSettings::setBottom(const qreal value)
    {
        if(value != mBottom){
            mBottom = value;
            applyBounds();
            bottomChanged();
        }
    }

    void ScreenProviderSettings::setLeft(const qreal value)
    {
        if(value != mLeft){
            mLeft = value;
            applyBounds();
            leftChanged();
        }
    }

    void ScreenProviderSettings::setRight(const qreal value)
    {
        if(value != mRight){
            mRight = value;
            applyBounds();
            rightChanged();
        }
    }

    void ScreenProviderSettings::setDepth(const qreal value)
    {
        if(value != mDepth){
            mDepth = value;
            applyDepth();
            depthChanged();
        }
    }

    void ScreenProviderSettings::applyBounds()
    {
        if(mProvider){
            luna::ScreenBounds bounds;
            bounds.xLow = static_cast<float>(mLeft);
            bounds.xHigh = static_cast<float>(mRight);
            bounds.yLow = static_cast<float>(1 - mTop);
            bounds.yHigh = static_cast<float>(1 - mBottom);
            mProvider->setBounds(bounds);
        }
    }

    void ScreenProviderSettings::applyDepth()
    {
        if(mProvider){
            mProvider->setDepth(std::lround(mDepth));
        }
    }

    void ScreenProviderSettings::setProvider(luna::Provider *provider)
    {
        mProvider = dynamic_cast<luna::ScreenProvider *>(provider);
        applyBounds();
        applyDepth();
    }

    void ScreenProviderSettings::setSettings(QSettings *settings)
    {
        ProviderSettings::setSettings(settings);
        mBottom = mSettings->value("screen/bottom", (qreal)0).toReal();
        mTop = mSettings->value("screen/top", (qreal)1).toReal();
        mLeft = mSettings->value("screen/left", (qreal)0).toReal();
        mRight = mSettings->value("screen/right", (qreal)1).toReal();
        mDepth = mSettings->value("screen/depth", (qreal)5).toReal();
        applyBounds();
        applyDepth();
    }
}


