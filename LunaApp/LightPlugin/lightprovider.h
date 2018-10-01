#ifndef LUNALightProvider_H
#define LUNALightProvider_H

#include <lunacore/provider.h>
#include <lunacore/colorspace.h>
#include <lunacore/colorutils.h>
#include <lunacore/strand.h>

#include "themecolor.h"

class LightProvider : public lunacore::Provider {
public:
    enum class Source {
        ColorPicker,
        Temperature,
        Manual,
        Theme,
    };

    LightProvider();

    void getData(std::vector<lunacore::Strand *> & strands) override;

    void setColor(const lunacore::Color & value);
    void setColorFromTemperature(const float value);
    void setWhiteness(lunacore::ColorScalar value);
    void setBrightness(lunacore::ColorScalar value);

    void setSource(Source value);
private:
    struct LightData {
        explicit LightData(lunacore::Strand * strand);
        lunacore::Color smoothColor;
        lunacore::ColorSpace::Transformation screenToStrandTransformation;
    };

    Source mSource;

    lunacore::Color mColor;
    lunacore::ColorScalar mWhiteness;

    ThemeColor mThemeColor;

    lunacore::ColorScalar mBrightness;

    lunacore::StrandData<LightData> mStrandData;
private:
    void update();
public:
    EIGEN_MAKE_ALIGNED_OPERATOR_NEW
};


#endif // LUNALightProvider_H
