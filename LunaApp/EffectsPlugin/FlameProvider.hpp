#pragma once

#include "Noise.hpp"

#include <luna/interface/Provider.hpp>

#include <chrono>

class FlameProvider : public luna::interface::Provider
{
public:
    explicit FlameProvider();
    void getData(luna::interface::Strand & strands) override;
    void update() override {};

    void temperatureLow(float value);
    void temperatureHigh(float value);
    void flickerRate(float value);
    void brightness(float value);
private:
    using clock = std::chrono::steady_clock;

    clock::time_point mStartTime;
    Noise mTemperatureNoise;

    float mTemperatureLow;
    float mTemperatureHigh;
    float mFlickerRate;
    float mBrightness;
};
