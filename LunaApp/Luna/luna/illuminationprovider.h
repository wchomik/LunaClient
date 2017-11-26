#ifndef LUNAILLUMINATIONPROVIDER_H
#define LUNAILLUMINATIONPROVIDER_H

#include "provider.h"
#include "themecolor.h"
#include "colorspace.h"

namespace luna {
    class IlluminationProvider : public Provider
    {
    public:
        IlluminationProvider();

        void getData(std::vector<class Strand *> & strands) override;

        void color(const Color & value){ mColor = value; }
        void whiteness(ColorScalar value){ mWhiteness = value; }

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

#endif // LUNAILLUMINATIONPROVIDER_H
