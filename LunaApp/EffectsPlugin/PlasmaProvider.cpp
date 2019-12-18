#include "PlasmaProvider.hpp"

#include <luna/interface/Strand.hpp>
#include <prism/Prism.hpp>

PlasmaProvider::PlasmaProvider() :
    mBeginTime(clock::now())
{}

void PlasmaProvider::getData(luna::interface::Strand & strand)
{
    Eigen::Vector3f mFrequency;
    float mHueChangeRate = 0.05f;

    mFrequency << 2, 2, 0.3f;
    auto now = clock::now();
    std::chrono::duration<float> timeDifference(now - mBeginTime);
    float t = timeDifference.count();

    for (size_t i = 0; i < strand.size(); ++i) {
        auto pixel = strand[i];
        auto position = pixel.position();
        position.z() += t;
        position = position.cwiseProduct(mFrequency);
        float hue = mNoise.at(position.x(), position.y(), position.z());
        prism::HSV hsv;
        hsv << hue + t * mHueChangeRate + 5, 1, 1.0f, 0;
        pixel.color(prism::RGBColorSpaceTransformation(prism::rec2020()).transform(prism::toRgb(hsv)));
    }
}

void PlasmaProvider::update()
{}
