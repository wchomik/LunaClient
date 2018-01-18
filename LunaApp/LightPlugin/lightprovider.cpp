#include "lightprovider.h"

#include <cstdint>
#include <lunacore/strand.h>

using namespace luna;

LightProvider::LightProvider() :
    mSource(Source::ColorPicker),
    mColor(1, 1, 1, 1),
    mWhiteness(0.0),
    mBrightness(1.0)
{
}

void LightProvider::getData(std::vector<Strand *> & strands) {
    constexpr float smoothScale = 0.04f;

    for (auto strand : strands) {
        Color lightColor = mColor;
        strand->setDirectColorMode();

        auto & data = mStrandData[strand];

        switch (mSource) {
        case Source::Manual:
            lightColor[3] = mWhiteness;
            break;
        case Source::Theme:
            lightColor = mThemeColor.get();
            // fallthrough
        case Source::ColorPicker:
            lightColor = data.screenToStrandTransformation * lightColor;
            lightColor[3] = 0.0;
            break;
        case Source::Temperature:
            lightColor = strand->config().colorSpace.fromXyzToRgb(lightColor);
            lightColor[3] = 0.0;
            break;
        }

        lightColor *= mBrightness;

        data.smoothColor = lerp(data.smoothColor, lightColor, smoothScale);

        strand->setAll(data.smoothColor);
    }
}

void LightProvider::setColor(const Color & value) {
    mColor = value;
}

void LightProvider::setColorFromTemperature(const float value) {
    mColor = temperatureToCieXyz(value);
}

void LightProvider::setWhiteness(ColorScalar value) {
    mWhiteness = value;
}

void LightProvider::setBrightness(ColorScalar value) {
    mBrightness = value;
}

void LightProvider::setSource(LightProvider::Source value) {
    mSource = value;
}

LightProvider::LightData::LightData(Strand * strand) :
    smoothColor(Color::Zero())
{
    screenToStrandTransformation =
        ColorSpace::combine(
            ColorSpace::rec2020(),
            strand->config().colorSpace);
}
