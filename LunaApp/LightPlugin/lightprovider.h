#ifndef LUNALightProvider_H
#define LUNALightProvider_H

#include <provider.h>
#include <colorspace.h>

#include "themecolor.h"

class LightProvider : public luna::Provider {
public:
    LightProvider();

    void getData(std::vector<luna::Strand *> & strands) override;

    void color(const luna::Color & value);
    void whiteness(luna::ColorScalar value);
    void shouldGetColorFromTheme(bool value);
private:
    luna::ColorSpace::Transformation mScreenToXyzTransformation;
    luna::ColorSpace::Transformation mColorToXyzTransformation;

    luna::Color mColor;
    luna::Color mSmoothColor;
    luna::ColorScalar mWhiteness;

    ThemeColor mThemeColor;
    bool mColorFromTheme;
private:
    void update();
public:
    EIGEN_MAKE_ALIGNED_OPERATOR_NEW
};


#endif // LUNALightProvider_H
