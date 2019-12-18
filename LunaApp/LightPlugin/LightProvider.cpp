#include "LightProvider.hpp"

#include <luna/interface/Strand.hpp>

#include <cstdint>

using namespace luna::interface;

LightProvider::LightProvider() :
    mCurrentColor(0, 0, 0, 0),
    mTargetColor(0, 0, 0, 0)
{}

LightProvider::~LightProvider() = default;

void LightProvider::getData(Strand & strand) {
    for (size_t i = 0; i < strand.size(); ++i) {
        strand[i].color(mCurrentColor);
    }
}

void LightProvider::update()
{
    constexpr float smoothScale = 0.04f;

    static_cast<prism::Coefficients &>(mCurrentColor) = mCurrentColor * (1 - smoothScale) + mTargetColor * smoothScale;
}

void LightProvider::color(prism::CieXYZ const & value) {
    mTargetColor = value;
}
