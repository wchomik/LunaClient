#include "screenprovider.h"

#include <cstdint>

#include <colorspace.h>
#include <strand.h>

using namespace Eigen;
using namespace luna;

void ScreenProvider::getData(std::vector<Strand *> & strands) {
    std::lock_guard<std::mutex> lock(mMutex);
    const bool hasNextFrame = mScreenCapture.getNextFrame();

    auto & screenPixels = mScreenCapture.pixels();

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
        strand->setSpaceConversionColorMode(ColorSpace::sRGB());

        const luna::ColorScalar tMul = 1.0f / std::max<float>(count - 1, 1);

        for (uint32_t i = 0; i < count; ++i) {
            const float t = static_cast<float>(i) * tMul;
            const Vector3f lightPosition = config.begin * (1.0f - t) + config.end * t;

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

            for (int i = 0; i < mDepth; ++i) {
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

void ScreenProvider::setBrightness(luna::ColorScalar value) {
    std::lock_guard<std::mutex> lock(mMutex);
    mBrightness = value;
    makeDepthWeights();
}

void ScreenProvider::setGamma(luna::ColorScalar value) {
    mGamma = value;
}

void ScreenProvider::setBlackLevel(ColorScalar value) {
    mBlackLevel = value;
}

void ScreenProvider::makeDepthWeights() {
    mDepthWeights = Eigen::ArrayXf::LinSpaced(mDepth, 1.0f, 1.0f / mDepth);
    mDepthWeights = mDepthWeights * (mBrightness / mDepthWeights.sum());
}

