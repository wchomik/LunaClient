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
    auto color = prism::sRGB().transform(mColor);
    color = prism::compressSRGB(color);
    static_cast<prism::Coefficients &>(color) = color.array().cwiseMax(0).cwiseMin(1);
    QColor ret;
    ret.setRgbF(color.x(), color.y(), color.z());
    return ret;
}

void LightModel::setColor(const QColor & value)
{
    prism::RGB rgb;
    rgb << value.redF(), value.greenF(), value.blueF(), 0;
    rgb = prism::linearizeSRGB(rgb);
    auto color = prism::sRGB().transform(rgb);

    if ((mColor - color).norm() > 0.001f) {
        mColor = color;
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

qreal LightModel::whiteness() const
{
    return mWhiteness;
}

void LightModel::setSource(int value) {
    if (mSource != value) {
        mSource = value;
        sourceChanged(mSource);
        notifyProvider();
    }
}

void LightModel::cieXYZ(qreal x, qreal y, qreal z)
{
    mColor << x, y, z, 0;
    mColor /= mColor.maxCoeff();

    colorChanged(color());

    notifyProvider();
}

void LightModel::setWhiteness(qreal value)
{
    if (mWhiteness != value) {
        mWhiteness = value;
        emit whitenessChanged(whiteness());
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
            color = mColor;
            break;
        case Source::Temperature:
            color = prism::temperature(mTemperature);
            break;
        case Source::Theme:
#if _WIN32
            color = mThemeColor.get();
#else
            color = mColor;
#endif
            break;
        }
        color *= mBrightness;
        color[3] = mWhiteness;

        p->color(color);
    }
}

