#include "strand.h"

#include "colorprocessor.h"

namespace luna {
    Strand::Strand(const Strand::Config & config) :
        mConfig(config),
        mPixels(config.count)
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
}
