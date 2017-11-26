#ifndef LUNALightProvider_H
#define LUNALightProvider_H

#include <provider.h>
#include <colorspace.h>
#include "win32/themecolor.h"

namespace luna {
    class LightProvider : public Provider {
    public:
        LightProvider();

        void getData(std::vector<class Strand *> & strands) override;

        Color color();
        void color(const Color & value);

        ColorScalar whiteness();
        void whiteness(ColorScalar value);

        bool shouldGetColorFromTheme();
        void shouldGetColorFromTheme(const bool value);
    private:
        Color mColor;
        ColorScalar mWhiteness;

        Color mSmoothColor;

        ThemeColor mThemeColor;
        bool mColorFromTheme;
    private:
        void update();
        ColorSpace::Transformation mScreenToXyzTransformation;
        ColorSpace::Transformation mColorToXyzTransformation;
    public:
        EIGEN_MAKE_ALIGNED_OPERATOR_NEW
    };
}

#endif // LUNALightProvider_H
