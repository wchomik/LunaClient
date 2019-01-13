#include "FlameProvider.hpp"

#include <luna/interface/Strand.hpp>
#include <prism/Prism.hpp>

using namespace Eigen;

FlameProvider::FlameProvider() :
    mStartTime(clock::now()),
    mTemperatureLow(1000.0f),
    mTemperatureHigh(5700.0f),
    mFlickerRate(0.2f),
    mBrightness(1.0f)
{}

void FlameProvider::getData(luna::interface::Strand & strand)
{
    std::chrono::duration<float> const diff = (clock::now() - mStartTime);
    auto const dt = diff.count();


    for (size_t i = 0; i < strand.size(); ++i) {
        auto pixel = strand[i];

        auto position = strand.beginPosition();
        position.x() += static_cast<float>(i) / static_cast<float>(strand.size()) * 3.0f - dt * 3.0f;
        position.y() += dt * 0.3743324f;

        auto baseTemperature = mTemperatureNoise.at(position) + 0.5f;

        auto smoothTemp = baseTemperature * (mTemperatureHigh - mTemperatureLow) + mTemperatureLow;

        auto const fadeFactor = std::pow(static_cast<float>(i) / static_cast<float>(strand.size() - 1), 3.0f);

        auto color = prism::temperature(smoothTemp);
        color *= mBrightness * std::max(0.0f, baseTemperature - fadeFactor);
        pixel.color(color);
    }
}

void FlameProvider::temperatureLow(float value)
{
    mTemperatureLow = value;
}

void FlameProvider::temperatureHigh(float value)
{
    mTemperatureHigh = value;
}

void FlameProvider::flickerRate(float value)
{
    mFlickerRate = value;
}

void FlameProvider::brightness(float value)
{
    mBrightness = value;
}
