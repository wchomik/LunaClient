#pragma once

#include <Eigen/Dense>

#include <cstdint>

namespace prism {
    namespace detail {
        using ColorScalar = float;
        using Coefficients = Eigen::Matrix<ColorScalar, 4, 1>;

        inline Coefficients lerp(Coefficients const & a, Coefficients const & b, ColorScalar t) {
            return a * (1.0 - t) + b * t;
        }

        template<typename T>
        constexpr const T & clamp(const T & value, const T & minimum, const T & maximum) {
            return (value < minimum) ? minimum : ((value > maximum) ? maximum : value);
        }
        
        template<typename T>
        const T modulus(const T value, const T divider) {
            T integral = std::floor(value / divider);
            return value - divider * integral;
        }
    }

    struct RGB {
        detail::Coefficients values;
    };

    struct CieXYZ {
        detail::Coefficients values;
    };

    struct HSV {
        detail::Coefficients values;
    };
    
    struct HSL {
        detail::Coefficients values;
    };

    HSV toHsv(RGB const & rgb);
    RGB toRgb(HSV const & hsv);

    HSL rgbToHsl(const RGB & rgb);
    RGB fromInteger(uint32_t integer);
    using CieXY = Eigen::Matrix<detail::ColorScalar, 2, 1>;

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
        typedef Eigen::Matrix<detail::ColorScalar, 4, 4> Transformation;

        Transformation mRgbToXyz;
        Transformation mXyzToRgb;
    };

    RGBColorSpace const & rec2020();
    RGBColorSpace const & ws2812();
    RGBColorSpace const & sRGB();

    RGB linearizeSRGB(RGB rgb);
    CieXYZ temperature(detail::ColorScalar kelvins);
}
