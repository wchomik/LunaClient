#include "screenprovider.h"

#include <cstdint>

#include <lunacore/colorspace.h>
#include <lunacore/strand.h>
#include <lunacore/range.h>

using namespace Eigen;
using namespace lunacore;

void ScreenProvider::getData(std::vector<Strand *> & strands) {
    std::lock_guard<std::mutex> lock(mMutex);
    const bool hasNextFrame = mScreenCapture.getNextFrame();

    auto & screenPixels = mScreenCapture.pixels();

    for (auto strand : strands) {
        const auto & config = strand->config();
        const uint32_t count = config.count;
        Color * const pixels = strand->pixels();
        if ((config.colorChannels & ColorChannels::rgb) != ColorChannels::rgb) {
            strand->setAll(Color::Zero());
            continue;
        }
        strand->setSpaceConversionColorMode(ColorSpace::sRGB());

        for (auto i : range(count)) {
            const Vector3f lightPosition = strand->positionOf(i);
            const float x = lightPosition.x();
            const float y = lightPosition.y();

            const float norm = std::max(std::abs(x), std::abs(y));

            float angle = ((x + y) / norm - 1.0f);
            if (x < y) {
                angle = 2.0f - angle;
            }
            angle += 8.0f;

            float integer;
            angle = std::modf(angle / 8.0f, &integer) * screenPixels.columns();

            const auto column = static_cast<int>(angle);

            Color sum = Color::Zero();

            for (auto i : range(mDepth)) {
                sum += screenPixels(column, i) * mDepthWeights[i];
            }
            sum = sum.cwiseMax(Color::Constant(mBlackLevel));
            sum[3] = 0;
            pixels[i] = sum;
        }
    }
}

ScreenProvider::ScreenProvider() :
    mBrightness(1.0f),
    mGamma(1.0f)
{
    setDepth(20);
    mScreenCapture.configure(256, 64);
}

void ScreenProvider::setDepth(int value) {
    std::lock_guard<std::mutex> lock(mMutex);
    mDepth = value;
    makeDepthWeights();
}

void ScreenProvider::setBrightness(lunacore::ColorScalar value) {
    std::lock_guard<std::mutex> lock(mMutex);
    mBrightness = value;
    makeDepthWeights();
}

void ScreenProvider::setGamma(lunacore::ColorScalar value) {
    mGamma = value;
}

void ScreenProvider::setBlackLevel(ColorScalar value) {
    mBlackLevel = value;
}

void ScreenProvider::makeDepthWeights() {
    mDepthWeights = Eigen::ArrayXf::LinSpaced(mDepth, 1.0f, 1.0f / mDepth);
    mDepthWeights = mDepthWeights * (mBrightness / mDepthWeights.sum());
}

