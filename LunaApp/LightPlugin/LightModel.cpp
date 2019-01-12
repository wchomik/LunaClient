#include "LightModel.hpp"

#include <prism/Prism.hpp>

using namespace luna::interface;

LightModel::LightModel() :
    mColor(),
    mTemperature(5500.0),
    mBrightness(1.0),
    mSource(0)
{}

LightModel::~LightModel() = default;

void LightModel::provider(std::weak_ptr<LightProvider> ptr)
{
    mProvider = ptr;
    notifyProvider();
}

QColor LightModel::color() const
{
    return mColor;
}

void LightModel::setColor(const QColor & value)
{
    if (mColor != value) {
        mColor = value;
        colorChanged(value);
        notifyProvider();
    }
}

qreal LightModel::temperature() const {
    return mTemperature;
}

void LightModel::setTemperature(qreal value) {
    if (mTemperature != value) {
        mTemperature = value;
        temperatureChanged(mTemperature);
        notifyProvider();
    }
}

qreal LightModel::brightness() const {
    return mBrightness;
}

void LightModel::setBrightness(qreal value) {
    if (mBrightness != value) {
        mBrightness = value;
        brightnessChanged(value);
        notifyProvider();
    }
}

int LightModel::source() const {
    return mSource;
}

void LightModel::setSource(int value) {
    if (mSource != value) {
        mSource = value;
        sourceChanged(mSource);
        notifyProvider();
    }
}

void LightModel::notifyProvider()
{
    if (auto p = mProvider.lock()) {
        auto source = static_cast<Source>(mSource);
        
        prism::CieXYZ color;
        switch (source) {
        case Source::ColorPicker:
            {
                prism::RGB rgb;
                rgb << mColor.redF(), mColor.greenF(), mColor.blueF(), mColor.alphaF();
                rgb = prism::linearizeSRGB(rgb);
                color = prism::sRGB().transform(rgb);
            }
            break;
        case Source::Temperature:
            color = prism::temperature(mTemperature);
            break;
        case Source::Theme:
            color = mThemeColor.get();
            break;
        }
        color *= mBrightness;

        p->color(color);
    }
}

