#include "ScreenProvider.hpp"

#include <cstdint>

#include <prism/Prism.hpp>
#include <luna/interface/Strand.hpp>

using namespace Eigen;
using namespace luna::interface;

namespace
{

int coordinatesToColumn(Eigen::Vector3f const & coordinates, int columnCount)
{
    float const x = coordinates.x();
    float const y = coordinates.y();

    float const norm = std::max(std::abs(x), std::abs(y));

    float angle = ((x + y) / norm - 1.0f);
    if (x < y) {
        angle = 2.0f - angle;
    }
    angle += 8.0f;

    float integer;
    angle = std::modf(angle / 8.0f, &integer) * columnCount;

    return static_cast<int>(angle);
}

template<typename T, typename U>
T lerp(T a, T b, U t)
{
    return a * (U(1) - t) + b * t;
}

}

void ScreenProvider::getData(Strand & strand)
{
    auto lock = std::lock_guard(mMutex);

    auto & screenPixels = mFilteredScreen;//mScreenCapture.pixels();

    auto const size = strand.size();

    auto transformation = prism::RGBColorSpaceTransformation(prism::sRGB());

    for (size_t i = 0; i < size; ++i) {
        auto pixel = strand[i];

        auto t0 = float(i) / float(size);
        auto t1 = float(i + 1) / float(size);

        auto const beginPosition = lerp(strand.beginPosition(), strand.endPosition(), t0);
        auto const endPosition = lerp(strand.beginPosition(), strand.endPosition(), t1);

        auto beginColumn = coordinatesToColumn(beginPosition, screenPixels.columns());
        auto endColumn = coordinatesToColumn(endPosition, screenPixels.columns());

        if (beginColumn > endColumn) {
            std::swap(beginColumn, endColumn);
        }

        Vector4f sum = Vector4f::Zero();

        for (int j = 0; j < mDepth; ++j) {
            for (int k = beginColumn; k <= endColumn; ++k) {
                sum += screenPixels(k, j) * mDepthWeights[j];
            }
        }

        sum /= endColumn - beginColumn + 1;
        sum += Vector4f::Constant(mBlackLevel);
        sum[3] = 0;

        prism::RGB rgb;
        static_cast<prism::Coefficients &>(rgb) = sum;

        pixel.color(transformation.transform(rgb));
    }
}

void ScreenProvider::update()
{
    mScreenCapture.getNextFrame();

    auto & screenPixels = mScreenCapture.pixels();

    for (size_t i = 0; i < mFilteredScreen.columns(); ++i) {
        for (size_t j = 0; j < mFilteredScreen.rows(); ++j) {
            mFilteredScreen(i, j) = mFilteredScreen(i, j) * mSmoothness + screenPixels(i, j) * (1.0f - mSmoothness);
        }
    }
}

ScreenProvider::ScreenProvider() :
    mFilteredScreen(256, 64),
    mBrightness(1.0f),
    mGamma(1.0f),
    mSmoothness(0.95f)
{
    setDepth(20);
    mScreenCapture.configure(256, 64);
}

void ScreenProvider::setDepth(int value) {
    std::lock_guard lock(mMutex);
    mDepth = value;
    makeDepthWeights();
}

void ScreenProvider::setBrightness(float value) {
    std::lock_guard lock(mMutex);
    mBrightness = value;
    makeDepthWeights();
}

void ScreenProvider::setGamma(float value) {
    mGamma = value;
}

void ScreenProvider::setBlackLevel(float value) {
    mBlackLevel = value;
}

void ScreenProvider::smoothness(float value)
{
    std::lock_guard lock(mMutex);
    mSmoothness = value;
}

void ScreenProvider::makeDepthWeights()
{
    mDepthWeights = Eigen::ArrayXf::LinSpaced(mDepth, 1.0f, 1.0f / mDepth);
    mDepthWeights = mDepthWeights * (mBrightness / mDepthWeights.sum());
}

