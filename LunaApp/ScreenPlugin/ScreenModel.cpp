#include "ScreenModel.hpp"

static const QString depthSettingName("depth");
static const QString brightnessSettingName("brightness");
static const QString gammaSettingName("gamma");
static const QString blackLevelSettingName("blackLevel");

ScreenModel::ScreenModel()
{
    mSettings.beginGroup("Screen");
    mDepth = mSettings.value(depthSettingName, 5.0).toReal();
    mBrightness = mSettings.value(brightnessSettingName, 1.0).toReal();
    mGamma = mSettings.value(gammaSettingName, 0.5).toReal();
    mBlackLevel = mSettings.value(blackLevelSettingName, 0.0).toReal();
}

ScreenModel::~ScreenModel()
{
    mSettings.setValue(depthSettingName, mDepth);
    mSettings.setValue(brightnessSettingName, mBrightness);
    mSettings.setValue(gammaSettingName, mGamma);
    mSettings.setValue(blackLevelSettingName, mBlackLevel);
}

void ScreenModel::provider(std::weak_ptr<ScreenProvider> ptr)
{
    mProvider = ptr;
    if (auto p = mProvider.lock()) {
        p->setDepth(std::lround(mDepth));
        p->setBrightness(mBrightness);
        p->setGamma(mGamma);
        p->setBlackLevel(mBlackLevel);
    }
}

void ScreenModel::setDepth(qreal const value)
{
    if (value == mDepth) {
        return;
    }

    mDepth = value;
    if (auto p = mProvider.lock()) {
        p->setDepth(std::lround(mDepth));
    }
    depthChanged(value);
}

void ScreenModel::setBrightness(qreal const value)
{
    if (value == mBrightness) {
        return;
    }

    mBrightness = value;
    if (auto p = mProvider.lock()) {
        p->setBrightness(static_cast<float>(mBrightness));
    }
    brightnessChanged(value);
}

void ScreenModel::setGamma(qreal const value)
{
    if (value == mGamma) {
        return;
    }

    mGamma = value;
    if (auto p = mProvider.lock()) {
        p->setGamma(mGamma);
    }
    gammaChanged(value);
}

void ScreenModel::setBlackLevel(qreal const value)
{
    if (mBlackLevel == value) {
        return;
    }

    mBlackLevel = value;
    if (auto p = mProvider.lock()) {
        p->setBlackLevel(mBlackLevel);
    }
    blackLevelChanged(value);
}

void ScreenModel::setSmoothness(qreal value)
{
    if (mSmoothness == value) {
        return;
    }

    mSmoothness = value;
    if (auto p = mProvider.lock()) {
        p->smoothness(mSmoothness);
    }
    smoothnessChanged(mSmoothness);
}


