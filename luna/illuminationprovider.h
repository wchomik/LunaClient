#ifndef LUNAILLUMINATIONPROVIDER_H
#define LUNAILLUMINATIONPROVIDER_H

#include "provider.h"
#include "themecolor.h"

namespace luna {
    class IlluminationProvider : public Provider
    {
    public:
        IlluminationProvider();
        virtual ~IlluminationProvider(){}
        void configure(const struct Config & config) override;
        ColorMode colorMode(class ColorSpace * outColorSpace) override;
        bool getData(std::vector<PixelStrand> & pixelStrands,
                    std::vector<ColorScalar> & whiteStrands) override;

        void color(const Color & value){ mColor = value; }
        void whiteness(ColorScalar value){ mWhiteness = value; }

        void shouldGetColorFromTheme(const bool value);
    private:
        Color mColor;
        ColorScalar mWhiteness;

        Color mSmoothColor;
        ColorScalar mSmoothWhiteness;

        ThemeColor mThemeColor;
        bool mColorFromTheme;
    private:
        void update();
    };
}

#endif // LUNAILLUMINATIONPROVIDER_H
