#ifndef COLORMODE_H
#define COLORMODE_H

namespace luna {
    enum class ColorMode {
        nativeDirect,
        nativeWhiteBalanced,
        nativeDirectGamma,
        nativeWhiteBalancedGamma,
        sRgb,
        rec2020,
    };
}

#endif // COLORMODE_H
