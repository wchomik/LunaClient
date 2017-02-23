#ifndef LUNACONFIG_H
#define LUNACONFIG_H

#include <vector>

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

        std::vector<PixelStrandConfig> pixelStrands;
        std::vector<Position> whiteStrands;
    };
}

#endif // LUNACONFIG_H
