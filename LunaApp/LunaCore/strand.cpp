#include "strand.h"

#include <range.h>

#include "colorprocessor.h"

namespace luna {
    Strand::Strand(const Strand::Config & config) :
        mConfig(config),
        mPixels(config.count),
        mPositionInterpolationFactor(1.0f / std::max<float>(config.count - 1, 1))
    {
        for(auto && pixel : mPixels){
            pixel.setZero();
        }
        setDirectColorMode();
    }

    const Strand::Config & Strand::config() const {
        return mConfig;
    }

    Color * Strand::pixels() {
        return mPixels.data();
    }

    Eigen::Vector3f Strand::positionOf(unsigned index) {
        const float t = static_cast<float>(index) * mPositionInterpolationFactor;
        return mConfig.begin * (1.0f - t) + mConfig.end * t;
    }

    void Strand::applyColorProcessing() {
        mColorProcessor->process(mPixels);
    }

    void Strand::setDirectColorMode() {
        mColorProcessor =
            std::make_unique<ColorProcessorDirect>();
    }

    void Strand::setSpaceConversionColorMode(const ColorSpace & sourceColorSpace) {
        mColorProcessor = std::make_unique<ColorProcessorColorSpace>(
            sourceColorSpace,
                    config().colorSpace);
    }

    void Strand::setAll(const Color & color) {
        for (auto i : range(mConfig.count)) {
            mPixels[i] = color;
        }
    }
}
