#include "illuminationprovider.h"

#include "config.h"

namespace luna {
    IlluminationProvider::IlluminationProvider() :
        mColor(1, 1, 1, 1),
        mWhiteness(0.0),
        mColorFromTheme(false),
        mSmoothColor(0.0, 0.0, 0.0, 0.0),
        mSmoothWhiteness(0.0f)
    {}

    void IlluminationProvider::configure(const Config &){}


    ColorMode IlluminationProvider::colorMode(class ColorSpace *)
    {
        ColorMode ret = ColorMode::fullDirect;
        if(mColorFromTheme) ret = ColorMode::colorSpaceConversion;
        return ret;
    }

    bool IlluminationProvider::getData(std::vector<PixelStrand> &pixelStrands, std::vector<ColorScalar> &whiteStrands)
    {
        Color lightColor;
        float lightWhiteness;
        if(mColorFromTheme) {
            lightColor = mThemeColor.get();
            lightWhiteness = 0;
        } else {
            lightColor = mColor;
            lightWhiteness = mWhiteness;
        }

        float smoothScale = 0.02f;
        mSmoothColor = lerp(mSmoothColor, lightColor, smoothScale);
        mSmoothWhiteness = mSmoothWhiteness * (1.0f - smoothScale)
            + lightWhiteness * smoothScale;

        for(PixelStrand & strand : pixelStrands){
            for(Color & pixel : strand){
                pixel = mSmoothColor;
            }
        }
        for(ColorScalar & strand : whiteStrands){
            strand = mSmoothWhiteness;
        }
        return true;
    }

    void IlluminationProvider::shouldGetColorFromTheme(const bool value) {
        if(value != mColorFromTheme) {
            //mSmoothWhiteness = mWhiteness;
            //mSmoothColor = mColor;
            mColorFromTheme = value;
        }
    }
}
