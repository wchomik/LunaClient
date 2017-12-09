#include "flamemodel.h"

#include "flameprovider.h"


static const QString temperatureLowSettingName("temperatureLow");
static const QString temperatureHighSettingName("temperatureHigh");
static const QString flickerRateSettingName("flickerRate");
static const QString brightnessSettingName("brightness");

FlameModel::FlameModel(QObject * parent) :
    QObject(parent),
    mSettings()
{
    mSettings.beginGroup("Flame");

    mTemperatureLow = mSettings.value(temperatureLowSettingName, 1000.0).value<qreal>();
    mTemperatureHigh = mSettings.value(temperatureHighSettingName, 5000.0).value<qreal>();
    mFlickerRate = mSettings.value(flickerRateSettingName, 0.2f).value<qreal>();
    mBrightness = mSettings.value(brightnessSettingName, 1.0).value<qreal>();
}

FlameModel::~FlameModel()
{
    mSettings.setValue(temperatureLowSettingName, mTemperatureLow);
    mSettings.setValue(temperatureHighSettingName, mTemperatureHigh);
    mSettings.setValue(flickerRateSettingName, mFlickerRate);
    mSettings.setValue(brightnessSettingName, mBrightness);
}

void FlameModel::provider(std::weak_ptr<FlameProvider> value)
{
    mProvider = value;
    if (auto p = mProvider.lock()) {
        p->temperatureLow(mTemperatureLow);
        p->temperatureHigh(mTemperatureHigh);
        p->flickerRate(mFlickerRate);
        p->brightness(mBrightness);
    }
}

qreal FlameModel::temperatureLow() const {
    return mTemperatureLow;
}

void FlameModel::setTemperatureLow(qreal value) {
    if (mTemperatureLow != value) {
        mTemperatureLow = value;
        if (auto p = mProvider.lock()) {
            p->temperatureLow(value);
        }
        temperatureLowChanged(value);
    }
}

qreal FlameModel::temperatureHigh() const {
    return mTemperatureHigh;
}

void FlameModel::setTemperatureHigh(qreal value) {
    if(mTemperatureHigh != value){
        mTemperatureHigh = value;
        if(auto p = mProvider.lock()) {
            p->temperatureHigh(value);
        }
        temperatureHighChanged(value);
    }
}

qreal FlameModel::flickerRate() const {
    return mFlickerRate;
}

void FlameModel::setFlickerRate(qreal value) {
    if(mFlickerRate != value){
        mFlickerRate = value;
        if(auto p = mProvider.lock()) {
            p->flickerRate(value);
        }
        flickerRateChanged(value);
    }
}
qreal FlameModel::brightness() const {
    return mBrightness;
}

void FlameModel::setBrightness(qreal value) {
    if(mBrightness != value){
        mBrightness = value;
        if(auto p = mProvider.lock()) {
            p->brightness(value);
        }
        brightnessChanged(value);
    }
}
