#include "flameprovider.h"

#include "strand.h"

using namespace Eigen;
using namespace luna;

constexpr static float sourceTemperatureLow = 1000.0f;
constexpr static float sourceTemperatureHigh = 3700.0f;
constexpr static float sourceChangeSpeed = 0.2f;

FlameProvider::FlameProvider() :
    mTemperatureDistribution(-1.0f, 1.0f),
    mSparkleDistribution(0.0001)
{
    mPreviousTime = mClock.now();
}

void FlameProvider::getData(std::vector<Strand *> & strands) {
    auto now = mClock.now();
    auto deltaTime = std::chrono::duration<float>(now - mPreviousTime).count();
    mPreviousTime = now;

    for (auto strand : strands) {
        const auto & config = strand->config();
        const uint32_t count = config.count;
        Color * const pixels = strand->pixels();
        if ((config.colorChannels & ColorChannels::rgb) != ColorChannels::rgb) {
            for (uint32_t i = 0; i < count; ++i) {
                pixels[i] = Color::Zero();
            }
            continue;
        }

        auto it = mStrandData.find(strand);
        if(mStrandData.end() == it) {
            createStrandData(strand);
        }
        StrandData & data = mStrandData[strand];

        data.burnRate += sourceChangeSpeed * mTemperatureDistribution(mRandom);
        // decay towards 1
        const float decayFactor = 1.0f - sourceChangeSpeed;
        data.burnRate = (data.burnRate - 1.0f) * decayFactor + 1.0f;


        // decay temperature and add sparkles
        const float coolRate = sourceTemperatureHigh / config.count;
        for (int i = 0; i < config.count; ++i) {
            float & temperature = data.temperatures[i];
            temperature -= coolRate;
            /*if (mSparkleDistribution(mRandom)) {
                temperature += 3000.0f;
            }*/
        }

        // shift whole strand
        data.shift += deltaTime * 100.0f;

        float shift;
        data.shift = std::modf(data.shift, &shift);

        auto shiftCount = 1;//static_cast<int>(shift);

        if (shiftCount > 0) {
            for (unsigned i = config.count - 1; i > 0; --i) {
                data.temperatures[i] = data.temperatures[i - 1];
            }
            data.temperatures[0] = data.burnRate * (sourceTemperatureHigh - sourceTemperatureLow) + sourceTemperatureLow;
        }

        // map to colors
        strand->setSpaceConversionColorMode(ColorSpace::cieXyz());

        for (unsigned i = 0; i < config.count; ++i) {
            int index = data.begin + data.direction * i;
            float temperature = data.temperatures[i];
            const float brightness = std::max(0.0f, (temperature - sourceTemperatureLow))
                / (sourceTemperatureHigh - sourceTemperatureLow);
            const float fadeStart = std::min(1.0f, i * 15.0f * config.count);
            Color color = temperatureToCieXyz(temperature) * brightness * fadeStart;
            strand->pixels()[index] = color;
        }
    }
}

void FlameProvider::createStrandData(Strand *strand) {
    auto & config = strand->config();
    StrandData & data = mStrandData[strand];
    data.temperatures.resize(config.count);
    for (float & t : data.temperatures) {
        t = 1000.0f;
    }

    Vector3f difference = config.end - config.begin;

    float slope = difference.y() / difference.norm();

    if (slope > 0) {
        data.direction = 1;
        data.begin = 0;
    } else {
        data.direction = -1;
        data.begin = config.count - 1;
    }
    data.speed = (1.0f + std::abs(slope)) * 0.5f;
    data.shift = 0.0f;
}
