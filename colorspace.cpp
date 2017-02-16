#include "colorspace.h"

#include <Eigen/Dense>

namespace luna {
    ColorSpace::ColorSpace(const cieCoord_t & white, const cieCoord_t & red,
                           const cieCoord_t & green, const cieCoord_t & blue)
    {
        mRgbToXyz << red.x(), green.x(), blue.x(), 0,
                    red.y(), green.y(), blue.y(), 0,
                    1 - red.x() - red.y(), 1 - green.x() - green.y(), 1 - blue.x() - blue.y(), 0,
                    0, 0, 0, 1;

        mXyzToRgb = mRgbToXyz.inverse();

        Color scale;
        scale << white.x(), white.y(), 1 - white.x() - white.y(), 1;
        scale = mXyzToRgb * (scale / white.y());
        Transformation scaleMatrix = Transformation::Zero();
        scaleMatrix.diagonal() = scale;

        mRgbToXyz = mRgbToXyz * scaleMatrix;
        mXyzToRgb = mRgbToXyz.inverse();
    }

    const ColorSpace & ColorSpace::sRGB()
    {
        static const ColorSpace ret(
            {0.31271, 0.32902f},
            {0.64,    0.33},
            {0.3,     0.6},
            {0.15,    0.06});
        return ret;
    }

    const ColorSpace & ColorSpace::rec2020()
    {
        static const ColorSpace ret(
            {0.31271, 0.32902},
            {0.708,   0.292},
            {0.170,   0.797},
            {0.131,   0.046});
        return ret;
    }

    const ColorSpace & ColorSpace::ws2812()
    {
        static const ColorSpace ret(
            {0.31271, 0.32902},
            {0.6918,  0.3047},
            {0.1887,  0.7161},
            {0.131,   0.07});
        return ret;
    }

    ColorSpace::Transformation ColorSpace::combine(const ColorSpace & from, const ColorSpace & to)
    {
       return to.mXyzToRgb * from.mRgbToXyz;
    }
}
