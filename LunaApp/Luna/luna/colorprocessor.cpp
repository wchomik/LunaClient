#include "colorprocessor.h"

namespace luna {

    ColorProcessor::~ColorProcessor() {}

    // direct
    void ColorProcessorDirect::process(luna::ColorVector &)
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
    ColorProcessorColorSpace::ColorProcessorColorSpace(const ColorSpace & src, const ColorSpace & dst, const Color & scale) {
        ColorSpace::Transformation scaleTransform;
        scaleTransform.setZero();
        scaleTransform.diagonal() = scale;
        mTransformation = scaleTransform * ColorSpace::combine(src, dst);
    }

    void ColorProcessorColorSpace::process(ColorVector & strand) {
        for (Color & pixel : strand) {
            pixel = mTransformation * pixel;
            clampColorToGamutAbsolute(pixel);
        }
    }


}
