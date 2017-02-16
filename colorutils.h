#ifndef COLORUTILS_H
#define COLORUTILS_H

#include <vector>

#include <Eigen/Core>
#include <Eigen/StdVector>

namespace luna {
    typedef float ColorScalar;
    typedef Eigen::Matrix<ColorScalar, 4, 1> Color;
    typedef std::vector<Color, Eigen::aligned_allocator<Color>> PixelStrand;
}

#endif // COLORUTILS_H
