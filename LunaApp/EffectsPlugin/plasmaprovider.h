#ifndef PLASMAPROVIDER_H
#define PLASMAPROVIDER_H

#include <chrono>

#include <lunacore/provider.h>

#include "noise.h"

class PlasmaProvider : public lunacore::Provider
{
public:
    PlasmaProvider();
    void getData(std::vector<lunacore::Strand *> & strands) override;
    Noise mNoise;
private:
    using clock = std::chrono::steady_clock;
    clock::time_point mBeginTime;
};

#endif // PLASMAPROVIDER_H
