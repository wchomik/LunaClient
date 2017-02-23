#include "colorprocessor.h"

namespace luna {
    // direct
    void ColorProcessorDirect::process(luna::PixelStrand & strand)
    {}

    // white balanced
    ColorProcessorWhiteBalanced::ColorProcessorWhiteBalanced(const Color &scale) :
        mScale(scale)
    {}

    void ColorProcessorWhiteBalanced::process(PixelStrand &strand)
    {
        for(Color & pixel : strand){
            pixel = pixel.cwiseProduct(mScale);
        }
    }

    // color space conversion
    ColorProcessorColorSpace::ColorProcessorColorSpace(const ColorSpace &src, const ColorSpace &dst, const Color &scale)
    {
        ColorSpace::Transformation scaleTransform;
        scaleTransform.setZero();
        scaleTransform.diagonal() = scale;
        mTransformation = scaleTransform * ColorSpace::combine(src, dst);
    }

    void ColorProcessorColorSpace::process(PixelStrand &strand)
    {
        for(Color & pixel : strand){
            pixel = mTransformation * pixel;
        }
    }


}
