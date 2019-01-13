#pragma once

#include <Eigen/Dense>

#include <cstdint>

namespace prism {

    using ColorScalar = float;
    using Coefficients = Eigen::Matrix<ColorScalar, 4, 1>;

    struct RGB : public Coefficients {
    };

    struct CieXYZ : public Coefficients {
    };

    struct HSV : public Coefficients {
    };
    
    struct HSL : public Coefficients {
    };

    HSV toHsv(RGB const & rgb);
    RGB toRgb(HSV const & hsv);

    HSL rgbToHsl(const RGB & rgb);
    RGB fromInteger(uint32_t integer);
    using CieXY = Eigen::Matrix<ColorScalar, 2, 1>;

    enum class RenderingIntent {
        RelativeColorimetric,
        AbsoluteColorimetric,
        Perceptual,
    };

    class RGBColorSpace
    {
    public:
        RGBColorSpace(CieXY const & white, CieXY const & red, CieXY const & green, CieXY const & blue);

        CieXYZ transform(RGB const & source) const;
        RGB transform(CieXYZ const & source, RenderingIntent intent = RenderingIntent::RelativeColorimetric) const;
    private:
        typedef Eigen::Matrix<ColorScalar, 4, 4> Transformation;

        Transformation mRgbToXyz;
        Transformation mXyzToRgb;
    };

    RGBColorSpace const & rec2020();
    RGBColorSpace const & ws2812();
    RGBColorSpace const & sRGB();

    RGB linearizeSRGB(RGB rgb);
    RGB compressSRGB(RGB rgb);

    CieXYZ temperature(ColorScalar kelvins);
}
