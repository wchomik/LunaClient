#include "LightModel.hpp"

#include <prism/Prism.hpp>

using namespace luna::interface;

Q_DECLARE_METATYPE(prism::CieXYZ)

LightModel::LightModel() :
    mGroup(&mSettings, "Light"),
    mColor(&mSettings, "color", prism::temperature(6500)),
    mTemperature(&mSettings, "temperature", 5500.0),
    mBrightness(&mSettings, "brightness", 1.0),
    mWhiteness(&mSettings, "whiteness", 1.0),
    mSource(&mSettings, "source", 0)
{}

LightModel::~LightModel() = default;

void LightModel::provider(std::weak_ptr<LightProvider> ptr)
{
    mProvider = ptr;
    notifyProvider();
}

QColor LightModel::color() const
{
    auto transformation = prism::RGBColorSpaceTransformation(prism::sRGB());
    auto color = transformation.transform(mColor);
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

    auto transformation = prism::RGBColorSpaceTransformation(prism::sRGB());
    auto color = transformation.transform(mColor);

    cieXYZ(color);
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

bool validCie(qreal v)
{
    return !std::isnan(v) && !std::isinf(v) && v > 0;
}

void LightModel::cieXYZ(qreal x, qreal y, qreal z)
{
    if (!(validCie(x) && validCie(y) && validCie(z))) {
        return;
    }

    prism::CieXYZ value(x, y, z, 0);
    value /= value.maxCoeff();
    cieXYZ(value);
}

void LightModel::cieXYZ(prism::CieXYZ value)
{
    if ((mColor.get() - value).norm() < 0.001f) {
        return;
    }

    mColor = value;
    colorChanged(color());
    notifyProvider();
}

void LightModel::setWhiteness(qreal value)
{
    if (mWhiteness != value) {
        mWhiteness = value;
        whitenessChanged(whiteness());
        notifyProvider();
    }
}

void LightModel::notifyProvider()
{
    if (auto p = mProvider.lock()) {
        auto source = static_cast<Source>(mSource.get());
        
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
        color[3] = std::pow(mWhiteness, 2.2);

        p->color(color);
    }
}

