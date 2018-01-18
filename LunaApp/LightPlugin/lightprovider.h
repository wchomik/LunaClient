#ifndef LUNALightProvider_H
#define LUNALightProvider_H

#include <lunacore/provider.h>
#include <lunacore/colorspace.h>
#include <lunacore/colorutils.h>
#include <lunacore/strand.h>

#include "themecolor.h"

class LightProvider : public luna::Provider {
public:
    enum class Source {
        ColorPicker,
        Temperature,
        Manual,
        Theme,
    };

    LightProvider();

    void getData(std::vector<luna::Strand *> & strands) override;

    void setColor(const luna::Color & value);
    void setColorFromTemperature(const float value);
    void setWhiteness(luna::ColorScalar value);
    void setBrightness(luna::ColorScalar value);

    void setSource(Source value);
private:
    struct LightData {
        explicit LightData(luna::Strand * strand);
        luna::Color smoothColor;
        luna::ColorSpace::Transformation screenToStrandTransformation;
    };

    Source mSource;

    luna::Color mColor;
    luna::ColorScalar mWhiteness;

    ThemeColor mThemeColor;

    luna::ColorScalar mBrightness;

    luna::StrandData<LightData> mStrandData;
private:
    void update();
public:
    EIGEN_MAKE_ALIGNED_OPERATOR_NEW
};


#endif // LUNALightProvider_H
