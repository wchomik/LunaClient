#include "flamemodel.h"

#include "flameprovider.h"



FlameModel::FlameModel(QObject * parent) :
    QObject(parent),
    mTemperatureLow(1000.0),
    mTemperatureHigh(5000.0),
    mFlickerRate(0.0),
    mBrightness(1.0)
{

}

FlameModel::~FlameModel()
{
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
