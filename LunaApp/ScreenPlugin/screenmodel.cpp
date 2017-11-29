#include "ScreenModel.h"

static const QString depthSettingName("depth");
static const QString brightnessSettingName("brightness");
static const QString gammaSettingName("gamma");


ScreenModel::ScreenModel(QObject * parent) :
    QObject(parent) {
    mSettings.beginGroup("Screen");
    mDepth = mSettings.value(depthSettingName, 5.0).toReal();
    mBrightness = mSettings.value(brightnessSettingName, 1.0).toReal();
    mGamma = mSettings.value(gammaSettingName, 0.5).toReal();

    if (auto p = mProvider.lock()) {
        p->setDepth(std::lround(mDepth));
        p->setBrightness(static_cast<float>(mBrightness));
        p->setGamma(mGamma);
    }
}

ScreenModel::~ScreenModel() {
    mSettings.setValue(depthSettingName, mDepth);
    mSettings.setValue(brightnessSettingName, mBrightness);
    mSettings.setValue(gammaSettingName, mGamma);
}

void ScreenModel::provider(std::weak_ptr<ScreenProvider> ptr) {
    mProvider = ptr;
    if (auto p = mProvider.lock()) {
        p->setDepth(std::lround(mDepth));
        p->setBrightness(static_cast<float>(mBrightness));
        p->setGamma(mGamma * 2);
    }
}

void ScreenModel::setDepth(const qreal value) {
    if (value == mDepth) {
        return;
    }

    mDepth = value;
    if (auto p = mProvider.lock()) {
        p->setDepth(std::lround(mDepth));
    }
    depthChanged();
}

void ScreenModel::setBrightness(const qreal value) {
    if (value == mBrightness) {
        return;
    }

    mBrightness = value;
    if (auto p = mProvider.lock()) {
        p->setBrightness(static_cast<float>(mBrightness));
    }
    brightnessChanged();
}

void ScreenModel::setGamma(const qreal value) {
    if (value != mGamma) {
        return;
    }

    mGamma = value;
    if (auto p = mProvider.lock()) {
        p->setGamma(mGamma);
    }
    gammaChanged();
}


