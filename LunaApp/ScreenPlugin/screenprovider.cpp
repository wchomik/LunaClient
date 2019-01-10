#include "ScreenProvider.hpp"

#include <cstdint>

#include <prism/Prism.hpp>
#include <luna/interface/Strand.hpp>

using namespace Eigen;
using namespace luna::interface;

void ScreenProvider::getData(Strand & strand)
{
    auto lock = std::lock_guard(mMutex);

    auto & screenPixels = mScreenCapture.pixels();

    auto size = strand.size();

    for (size_t i = 0; i < size; ++i) {
        auto pixel = strand[i];
        auto lightPosition = pixel.position();
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

        Vector4f sum = Vector4f::Zero();

        for (int i = 0; i < mDepth; ++i) {
            sum += screenPixels(column, i) * mDepthWeights[i];
        }
        sum = sum.cwiseMax(Vector4f::Constant(mBlackLevel));
        sum[3] = 0;

        prism::RGB rgb;
        rgb.values = sum;

        pixel.color(prism::sRGB().transform(rgb));
    }
}

void ScreenProvider::update()
{
    mScreenCapture.getNextFrame();
}

ScreenProvider::ScreenProvider() :
    mBrightness(1.0f),
    mGamma(1.0f)
{
    setDepth(20);
    mScreenCapture.configure(256, 64);
}

void ScreenProvider::setDepth(int value) {
    mDepth = value;
    makeDepthWeights();
}

void ScreenProvider::setBrightness(float value) {
    mBrightness = value;
    makeDepthWeights();
}

void ScreenProvider::setGamma(float value) {
    mGamma = value;
}

void ScreenProvider::setBlackLevel(float value) {
    mBlackLevel = value;
}

void ScreenProvider::makeDepthWeights()
{
    std::lock_guard lock(mMutex);
    mDepthWeights = Eigen::ArrayXf::LinSpaced(mDepth, 1.0f, 1.0f / mDepth);
    mDepthWeights = mDepthWeights * (mBrightness / mDepthWeights.sum());
}

