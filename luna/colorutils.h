#ifndef COLORUTILS_H
#define COLORUTILS_H

#include <vector>

#include <Eigen/Core>
#include <Eigen/StdVector>

namespace luna {
    typedef float ColorScalar;
    typedef Eigen::Matrix<ColorScalar, 4, 1> Color;
    typedef std::vector<Color, Eigen::aligned_allocator<Color>> PixelStrand;

    void hsvToRgb(Color & ret, const Color & hsv);
    Color uintToColor(uint32_t integer);

    inline Color lerp(const Color & a, const Color & b, float t) {
        return a * (1.0f - t) + b * t;
    }
}

#endif // COLORUTILS_H
