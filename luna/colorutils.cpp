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

}
