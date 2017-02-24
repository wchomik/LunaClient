#ifndef LUNAPROVIDER_H
#define LUNAPROVIDER_H

#include <vector>
#include "colorutils.h"
#include "colormode.h"

namespace luna {
    class Provider
    {
    public:
        virtual ~Provider(){}
        virtual void configure(const struct Config & config) = 0;
        virtual ColorMode colorMode(class ColorSpace * outColorSpace) = 0;
        virtual bool getData(std::vector<PixelStrand> & pixelStrands,
            std::vector<ColorScalar> & whiteStrands) = 0;
    };
}

#endif // LUNAPROVIDER_H
