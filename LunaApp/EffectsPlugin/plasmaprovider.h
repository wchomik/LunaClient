#ifndef PLASMAPROVIDER_H
#define PLASMAPROVIDER_H

#include <chrono>

#include <provider.h>

#include "noise.h"

class PlasmaProvider : public luna::Provider
{
public:
    PlasmaProvider();
    void getData(std::vector<luna::Strand *> & strands) override;
    Noise mNoise;
private:
    using clock = std::chrono::steady_clock;
    clock::time_point mBeginTime;
};

#endif // PLASMAPROVIDER_H
