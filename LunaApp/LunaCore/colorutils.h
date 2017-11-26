#ifndef COLORUTILS_H
#define COLORUTILS_H

#include <vector>

#include <Eigen/Core>
#include <Eigen/StdVector>

#include "lunacore_global.h"

namespace luna {
    typedef float ColorScalar;
    typedef Eigen::Matrix<ColorScalar, 4, 1> Color;
    typedef std::vector<Color, Eigen::aligned_allocator<Color>> ColorVector;

    Color LUNACORESHARED_EXPORT rgbToHsv(const Color & rgb);
    Color LUNACORESHARED_EXPORT hsvToRgb(const Color & hsv);
    Color LUNACORESHARED_EXPORT uintToColor(uint32_t integer);
    Color LUNACORESHARED_EXPORT temperatureToCieXyz(float temperature);

    inline Color lerp(const Color & a, const Color & b, float t) {
        return a * (1.0f - t) + b * t;
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

    void LUNACORESHARED_EXPORT clampColorToGamutRelative(Color & color);
    void LUNACORESHARED_EXPORT clampColorToGamutAbsolute(Color & color);
}

#endif // COLORUTILS_H
