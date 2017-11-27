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

        void color(const Color & value);
        void whiteness(ColorScalar value);
        void shouldGetColorFromTheme(bool value);
    private:
        ColorSpace::Transformation mScreenToXyzTransformation;
        ColorSpace::Transformation mColorToXyzTransformation;

        Color mColor;
        Color mSmoothColor;
        ColorScalar mWhiteness;

        ThemeColor mThemeColor;
        bool mColorFromTheme;
    private:
        void update();
    public:
        EIGEN_MAKE_ALIGNED_OPERATOR_NEW
    };
}

#endif // LUNALightProvider_H
