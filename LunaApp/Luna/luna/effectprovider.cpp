#include "effectprovider.h"

#include "strand.h"

using namespace Eigen;

namespace luna {
    EffectProvider::EffectProvider() :
        mTemperatureDistribution(1000.0f, 4000.0f),
        mSparkleDistribution(0.0001)
    {
        mPreviousTime = mClock.now();
    }
    EffectProvider::~EffectProvider() {}

    void EffectProvider::getData(std::vector<Strand *> & strands) {
        auto now = mClock.now();
        auto deltaTime = std::chrono::duration<float>(now - mPreviousTime).count();
        mPreviousTime = now;

        for (auto strand : strands) {
            auto & config = strand->config();

            if ((config.colorChannels & ColorChannels::rgb) != ColorChannels::rgb) continue;

            auto it = mStrandData.find(strand);
            if(mStrandData.end() == it) {
                createStrandData(strand);
            }
            StrandData & data = mStrandData[strand];

            // decay temperature and add sparkles
            for (int i = 0; i < config.count; ++i) {
                float & temperature = data.temperatures[i];
                temperature = (temperature - 1000.0f) * std::exp(-deltaTime) + 1000.0f;
                if (mSparkleDistribution(mRandom)) {
                    temperature += 3000.0f;
                }
            }

            // shift whole strand
            data.shift += deltaTime * 40.0f;

            float shift;
            data.shift = std::modf(data.shift, &shift);

            auto shiftCount = static_cast<int>(shift);

            if (shiftCount > 0) {
                for (int i = config.count - 1; i > 0; --i) {
                    data.temperatures[i] = data.temperatures[i - 1];
                }
                data.temperatures[0] = mTemperatureDistribution(mRandom);
            }

            // map to colors
            strand->setSpaceConversionColorMode(ColorSpace::cieXyz());
            for (int i = 0; i < config.count; ++i) {
                int index = data.begin + data.direction * i;
                float temperature = data.temperatures[i];
                Color color = temperatureToCieXyz(temperature) * ((temperature - 1000.0f) / 2000.0f);
                strand->pixels()[index] = color;
            }
        }
    }

    void EffectProvider::createStrandData(Strand *strand) {
        auto & config = strand->config();
        StrandData & data = mStrandData[strand];
        data.temperatures.resize(config.count);

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

}
