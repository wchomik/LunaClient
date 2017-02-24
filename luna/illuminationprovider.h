#ifndef LUNAILLUMINATIONPROVIDER_H
#define LUNAILLUMINATIONPROVIDER_H

#include "provider.h"

namespace luna {
    class IlluminationProvider : public Provider
    {
    public:
        IlluminationProvider();

        void configure(const struct Config & config) override;
        ColorMode colorMode(class ColorSpace * outColorSpace) override;
        bool getData(std::vector<PixelStrand> & pixelStrands,
                    std::vector<ColorScalar> & whiteStrands) override;

        void color(const Color & value){ mColor = value; mNewData = true; }
        void whiteness(ColorScalar value){ mWhiteness = value; mNewData = true; }
    private:
        Color mColor;
        ColorScalar mWhiteness;
        bool mNewData;
    private:
        void update();
    };
}

#endif // LUNAILLUMINATIONPROVIDER_H
