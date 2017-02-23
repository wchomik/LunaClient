#include "colorprocessor.h"

namespace luna {
    // direct
    void ColorProcessorDirect::process(luna::PixelStrand & strand)
    {}

    // direct gamma
    ColorProcessorDirectGamma::ColorProcessorDirectGamma(ColorScalar gamma) :
        mGamma(gamma)
    {}

    void ColorProcessorDirectGamma::gamma(ColorScalar value){
        mGamma = value;
    }

    ColorScalar ColorProcessorDirectGamma::gamma(){
        return mGamma;
    }

    void ColorProcessorDirectGamma::process(PixelStrand & strand)
    {
        for(Color & pixel : strand){
            pixel = pixel.array().pow(mGamma).matrix();
        }
    }

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

    // white balanced with gamma
    ColorProcessorWhiteBalancedGamma::ColorProcessorWhiteBalancedGamma(const Color &scale, ColorScalar gamma) :
        mScale(scale),
        mGamma(gamma)
    {}

    void ColorProcessorWhiteBalancedGamma::gamma(ColorScalar value){
        mGamma = value;
    }

    ColorScalar ColorProcessorWhiteBalancedGamma::gamma(){
        return mGamma;
    }

    void ColorProcessorWhiteBalancedGamma::process(PixelStrand &strand)
    {
        for(Color & pixel : strand){
            pixel = pixel.array().pow(mGamma).matrix().cwiseProduct(mScale);
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
