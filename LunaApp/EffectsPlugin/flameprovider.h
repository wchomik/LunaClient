#ifndef EFFECTPROVIDER_H
#define EFFECTPROVIDER_H

#include <unordered_map>
#include <chrono>
#include <random>

#include "provider.h"


class FlameProvider : public luna::Provider
{
public:
    FlameProvider();
    void getData(std::vector<luna::Strand *> &strands) override;

    void temperatureLow(float value);
    void temperatureHigh(float value);
    void flickerRate(float value);
    void brightness(float value);
private:
    struct StrandData {
        std::vector<float> temperatures;
        int begin;
        int direction;
        float speed;
        float shift;
        float burnRate;
    };
    void createStrandData(luna::Strand * strand);
    std::unordered_map<luna::Strand *, StrandData> mStrandData;
    std::chrono::steady_clock mClock;
    std::chrono::steady_clock::time_point mPreviousTime;
    std::default_random_engine mRandom;
    std::uniform_real_distribution<float> mTemperatureDistribution;
    std::bernoulli_distribution mSparkleDistribution;

    float mTemperatureLow;
    float mTemperatureHigh;
    float mFlickerRate;
    float mBrightness;
};


#endif // EFFECTPROVIDER_H
