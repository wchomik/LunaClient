#ifndef COLORUTILS_H
#define COLORUTILS_H

#include <vector>

#include <Eigen/Core>
#include <Eigen/StdVector>

namespace luna {
    typedef float ColorScalar;
    typedef Eigen::Matrix<ColorScalar, 4, 1> Color;
    typedef std::vector<Color, Eigen::aligned_allocator<Color>> ColorVector;

    Color rgbToHsv(const Color & rgb);
    Color hsvToRgb(const Color & hsv);
    Color uintToColor(uint32_t integer);
    Color temperatureToCieXyz(float temperature);

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

    void clampColorToGamutRelative(Color & color);
    void clampColorToGamutAbsolute(Color & color);
}

#endif // COLORUTILS_H
