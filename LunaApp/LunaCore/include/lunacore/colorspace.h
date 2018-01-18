#ifndef COLORSPACE_H
#define COLORSPACE_H

#include <Eigen/Core>

#include "lunacore_global.h"
#include "colorutils.h"

namespace luna {
    class LUNACORESHARED_EXPORT ColorSpace
    {
        typedef Eigen::Matrix<ColorScalar, 2, 1> cieCoord_t;
    public:
        ColorSpace();
        ColorSpace(const cieCoord_t & white, const cieCoord_t & red,
                   const cieCoord_t & green, const cieCoord_t & blue);

        Color fromRgbToXyz(const Color & source) const;
        Color fromXyzToRgb(const Color & source) const;

        typedef Eigen::Matrix<ColorScalar, 4, 4> Transformation;

        static const ColorSpace & cieXyz();
        static const ColorSpace & sRGB();
        static const ColorSpace & rec2020();
        static const ColorSpace & ws2812();

        static Transformation combine(const ColorSpace & from, const ColorSpace & to);
    private:
        Transformation mRgbToXyz;
        Transformation mXyzToRgb;
    public:
        EIGEN_MAKE_ALIGNED_OPERATOR_NEW
    };
}
#endif // COLORSPACE_H
