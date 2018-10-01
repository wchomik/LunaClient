#include "colorprocessor.h"

namespace lunacore {

    ColorProcessor::~ColorProcessor() {}

    // direct
    void ColorProcessorDirect::process(lunacore::ColorVector &)
    {}

    // white balanced
    ColorProcessorWhiteBalanced::ColorProcessorWhiteBalanced(const Color & scale) :
        mScale(scale)
    {}

    void ColorProcessorWhiteBalanced::process(ColorVector & strand) {
        for (Color & pixel : strand){
            pixel = pixel.cwiseProduct(mScale);
        }
    }

    // color space conversion
    ColorProcessorColorSpace::ColorProcessorColorSpace(const ColorSpace & src, const ColorSpace & dst) {
        mTransformation = ColorSpace::combine(src, dst);
    }

    void ColorProcessorColorSpace::process(ColorVector & strand) {
        for (Color & pixel : strand) {
            pixel = mTransformation * pixel;
            clampColorToGamutAbsolute(pixel);
        }
    }


}
