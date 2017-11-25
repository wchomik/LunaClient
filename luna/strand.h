#ifndef STRAND_H
#define STRAND_H

#include <vector>
#include <memory>
#include <cstdint>
#include "colormode.h"
#include "colorutils.h"
#include "colorspace.h"
#include "colorprocessor.h"

namespace luna {
    enum ColorChannels {
        red = 1 << 0,
        green = 1 << 1,
        blue = 1 << 2,
        white = 1 << 3,
        rgb = red | green | blue,
    };

    class Strand
    {
    public:
        struct Config {
            ColorSpace colorSpace;
            ColorChannels colorChannels;
            Color whiteBalance;
            uint32_t count;
            Eigen::Vector3f begin;
            Eigen::Vector3f end;

            EIGEN_MAKE_ALIGNED_OPERATOR_NEW
        };
        Strand(const Config & config);

        const Config & config() const;
        Color * pixels();

        void applyColorProcessing();

        void setDirectColorMode();
        void setWhiteBalancedColorMode();
        void setSpaceConversionColorMode(const ColorSpace & sourceColorSpace);
    private:
        Config mConfig;
        ColorVector mPixels;
        std::unique_ptr<ColorProcessor> mColorProcessor;
    public:
        EIGEN_MAKE_ALIGNED_OPERATOR_NEW
    };
}

#endif // STRAND_H
