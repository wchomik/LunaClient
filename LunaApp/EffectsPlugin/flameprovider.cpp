#include "flameprovider.h"

#include <lunacore/strand.h>

using namespace Eigen;
using namespace lunacore;

FlameProvider::FlameProvider() :
    mTemperatureDistribution(-1.0f, 1.0f),
    mSparkleDistribution(0.0001),
    mTemperatureLow(1000.0f),
    mTemperatureHigh(5700.0f),
    mFlickerRate(0.2f),
    mBrightness(1.0f) {
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
        if (mStrandData.end() == it) {
            createStrandData(strand);
        }
        StrandData & data = mStrandData[strand];

        data.burnRate += mFlickerRate * mTemperatureDistribution(mRandom) * 2.0f;

        const float decayFactor = 1.0f - mFlickerRate;
        data.burnRate = (data.burnRate - 0.5f) * decayFactor + 0.5f;
        data.burnRate = clamp(data.burnRate, 0.0f, 1.0f);

        for (unsigned i = config.count - 1; i > 0; --i) {
            data.temperatures[i] = data.temperatures[i - 1];
        }
        data.temperatures[0] = data.burnRate;

        // map to colors
        strand->setSpaceConversionColorMode(ColorSpace::cieXyz());

        for (unsigned i = 0; i < config.count; ++i) {
            float temperature = data.temperatures[i] - static_cast<float>(i) / static_cast<float>(config.count);
            const float brightness = std::sqrt(std::max(0.0f, temperature)) * mBrightness;
            const float fadeStart = std::min(1.0f, i * 15.0f * config.count);
            Color color = temperatureToCieXyz(temperature * (mTemperatureHigh - mTemperatureLow) + mTemperatureLow) * brightness * fadeStart;

            int index = data.begin + data.direction * i;
            strand->pixels()[index] = color;
        }
    }
}

void FlameProvider::temperatureLow(float value) {
    mTemperatureLow = value;
}

void FlameProvider::temperatureHigh(float value) {
    mTemperatureHigh = value;
}

void FlameProvider::flickerRate(float value) {
    mFlickerRate = value;
}

void FlameProvider::brightness(float value) {
    mBrightness = value;
}

void FlameProvider::createStrandData(Strand * strand) {
    auto & config = strand->config();
    StrandData & data = mStrandData[strand];
    data.temperatures.resize(config.count);
    for (float & t : data.temperatures) {
        t = 0.0f;
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
