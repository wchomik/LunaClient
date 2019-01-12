#pragma once

#include "Noise.hpp"

#include <luna/interface/Provider.hpp>

#include <chrono>

class PlasmaProvider : public luna::interface::Provider
{
public:
    explicit PlasmaProvider();
    void getData(luna::interface::Strand & strands) override;
    void update() override;

private:
    Noise mNoise;
    using clock = std::chrono::steady_clock;
    clock::time_point mBeginTime;
};
