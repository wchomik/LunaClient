#include "lightprovider.h"

#include <cstdint>
#include <strand.h>

namespace luna {
    LightProvider::LightProvider() :
        mColor(1, 1, 1, 1),
        mWhiteness(0.0),
        mSmoothColor(0.0, 0.0, 0.0, 0.0),
        mColorFromTheme(false)
    {
        mScreenToXyzTransformation =
            ColorSpace::combine(
                ColorSpace::sRGB(),
                ColorSpace::cieXyz());

        mScreenToXyzTransformation =
            ColorSpace::combine(
                ColorSpace::rec2020(),
                ColorSpace::cieXyz());
    }

    void LightProvider::getData(std::vector<Strand *> & strands) {
        Color lightColor;
        if (mColorFromTheme) {
            lightColor = mScreenToXyzTransformation * mThemeColor.get();
            lightColor[3] = 0.0f;
        } else {
            lightColor = mScreenToXyzTransformation * mColor;
            lightColor[3] = mWhiteness;
        }

        const float smoothScale = 0.05f;
        mSmoothColor = lerp(mSmoothColor, lightColor, smoothScale);

        for (auto && strand : strands) {
            strand->setSpaceConversionColorMode(ColorSpace::cieXyz());
            uint32_t count = strand->config().count;
            Color * pixels = strand->pixels();
            for (uint32_t i = 0; i < count; ++i) {
                pixels[i] = mSmoothColor;
            }
        }
    }

    void LightProvider::color(const Color & value) {
        mColor = value;
    }

    void LightProvider::whiteness(ColorScalar value) {
        mWhiteness = value;
    }

    void LightProvider::shouldGetColorFromTheme(bool value) {
        mColorFromTheme = value;
    }
}
