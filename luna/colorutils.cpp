#include "colorutils.h"

#include <cmath>

namespace luna {

    void hsvToRgb(Color & ret, const Color & hsv)
    {
        ColorScalar i;
        ColorScalar h6 = modf(hsv[0], &i) * 6;
        ColorScalar sat = hsv[1];
        ColorScalar val = hsv[2];
        ret = Color(
            std::abs(3 - h6) - 1,
            2 - std::abs(2 - h6),
            2 - std::abs(4 - h6),
            0);
        ret = (ret.cwiseMax(0).cwiseMin(1) * sat + Color::Constant(1 - sat)) * val;
    }

    Color uintToColor(uint32_t integer){
        auto r = (integer & 0x000000ff) >> 0;
        auto g = (integer & 0x0000ff00) >> 8;
        auto b = (integer & 0x00ff0000) >> 16;
        return Color(r / 255.0f, g / 255.0f, b / 255.0f, 0.0f);
    }

}
