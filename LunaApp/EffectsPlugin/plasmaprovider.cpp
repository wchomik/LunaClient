#include "plasmaprovider.h"

using namespace luna;

#include <strand.h>
#include <range.h>
#include <colorutils.h>

PlasmaProvider::PlasmaProvider() :
    mBeginTime(clock::now())
{}

void PlasmaProvider::getData(std::vector<Strand *> & strands) {
    Eigen::Vector3f mFrequency;
    float mHueChangeRate = 0.05f;

    mFrequency << 2, 2, 0.3f;
    auto now = clock::now();
    std::chrono::duration<float> timeDifference(now - mBeginTime);
    float t = timeDifference.count();

    for (auto strand : strands) {
        strand->setSpaceConversionColorMode(luna::ColorSpace::rec2020());
        auto config = strand->config();
        if ((config.colorChannels & ColorChannels::rgb) != ColorChannels::rgb) {
            strand->setAll(Color::Zero());
            continue;
        }

        for (auto i : range(config.count)) {
            auto position = strand->positionOf(i);
            position.z() += t;
            position = position.cwiseProduct(mFrequency);
            float hue = mNoise.at(position.x(), position.y(), position.z());
            Color c(hue + t * mHueChangeRate, 1, 0.8f, 0);
            strand->pixels()[i] = hsvToRgb(c);
        }
    }
}
