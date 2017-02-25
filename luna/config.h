#ifndef LUNACONFIG_H
#define LUNACONFIG_H

#include <vector>
#include "colorspace.h"

namespace luna {
    struct Config {
        enum Position {
            top,
            right,
            bottom,
            left,
        };
        enum Direction {
            leftToRight,
            rightToLeft,
            topToBottom,
            bottomToTop,
        };

        struct PixelStrandConfig {
            int count;
            Position position;
            Direction direction;
        };

        ColorSpace colorSpace;
        std::vector<PixelStrandConfig> pixelStrands;
        std::vector<Position> whiteStrands;

    public:
        EIGEN_MAKE_ALIGNED_OPERATOR_NEW
    };
}

#endif // LUNACONFIG_H
