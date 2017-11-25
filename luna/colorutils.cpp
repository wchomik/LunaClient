#include "colorutils.h"

#include <cmath>
#include <algorithm>

namespace luna {
    Color rgbToHsv(const Color &rgb) {
        ColorScalar minimum, maximum, chroma,
            hue = 0.0f,
            saturation = 0.0f,
            value = 0.0f;

        minimum = std::min<ColorScalar>({rgb[0], rgb[1], rgb[3]});
        maximum = std::max<ColorScalar>({rgb[0], rgb[1], rgb[3]});
        if(maximum != 0.0f) {
            chroma = maximum - minimum;

            hue = 0;
            if (rgb[0] == maximum) {
                hue =( rgb[1] - rgb[2]) / chroma;
                if (hue < 0) hue += 6;
            } else if (rgb[1] == maximum) {
                hue = (rgb[2] - rgb[0]) / chroma;
            }else if (rgb[2] == maximum) {
                hue = (rgb[0] - rgb[1]) / chroma;
            }
            hue /= 6.0f;

            value = maximum;

            saturation = chroma / value;
        }

        Color hsv;
        hsv << hue, saturation, value, rgb[3];
        return hsv;
    }

    Color hsvToRgb(const Color & hsv)
    {
        ColorScalar i;
        ColorScalar h6 = modf(hsv[0], &i) * 6;
        ColorScalar sat = clamp(hsv[1], 0.0f, 1.0f);
        ColorScalar val = clamp(hsv[2], 0.0f, 1.0f);

        Color rgb;
        rgb << std::abs(3 - h6) - 1,
            2 - std::abs(2 - h6),
            2 - std::abs(4 - h6),
            0;

        rgb = (rgb.cwiseMax(0).cwiseMin(1) * sat + Color::Constant(1 - sat)) * val;
        rgb[3] = hsv[3];
        return rgb;
    }

    Color uintToColor(uint32_t integer) {
        auto r = (integer & 0x000000ff) >> 0;
        auto g = (integer & 0x0000ff00) >> 8;
        auto b = (integer & 0x00ff0000) >> 16;
        auto a = (integer & 0xff000000) >> 24;
        return Color(r / 255.0f, g / 255.0f, b / 255.0f, a / 255.0f);
    }

    void clampColorToGamutRelative(Color & color) {
        ColorScalar minimum, maximum;
        minimum = std::min<ColorScalar>({color[0], color[1], color[2], 0.0f});

        maximum = std::max<ColorScalar>({color[0], color[1], color[2], 1.0f});

        /*
         * f(x) = a * x + b;
         * a = (y2 - y1) / (x2 - x1)
         * b = (x2y1 - x1y2)/(x2 - x1)
         * x1 = min
         * x2 = max
         * y1 = 0
         * y2 = 1
        */

        ColorScalar scale = 1.0f / (maximum - minimum);
        ColorScalar offset = -minimum * scale;
        ColorScalar w = color[3];
        color = color * scale + Color::Constant(offset);
        color[3] = w;
    }

    void clampColorToGamutAbsolute(Color & color)
    {
        static const Color minimum(0.0f, 0.0f, 0.0f, 0.0f);
        static const Color maximum(1.0f, 1.0f, 1.0f, 1.0f);
        color = color.cwiseMax(minimum).cwiseMin(maximum);
    }

}
