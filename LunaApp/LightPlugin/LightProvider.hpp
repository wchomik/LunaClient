#pragma once

#include <luna/interface/Provider.hpp>
#include <prism/Prism.hpp>

class LightProvider : public luna::interface::Provider {
public:
    explicit LightProvider();
    ~LightProvider() override;
    void getData(luna::interface::Strand & strand) override;
    void update() override;

    void color(const prism::CieXYZ & value);
private:
    prism::CieXYZ mCurrentColor;
    prism::CieXYZ mTargetColor;

};
