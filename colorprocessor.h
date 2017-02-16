#ifndef COLORPROCESSOR_H
#define COLORPROCESSOR_H

#include "colorutils.h"
#include "colorspace.h"

namespace luna {
    class ColorProcessor
    {
    public:
        virtual ~ColorProcessor(){}
        virtual void process(PixelStrand & strand) = 0;
    };

    class ColorProcessorDirect : public ColorProcessor {
    public:
        void process(PixelStrand & strand) override;
    };

    class ColorProcessorDirectGamma : public ColorProcessor {
    public:
        ColorProcessorDirectGamma(ColorScalar gamma = 2.2);
        void gamma(ColorScalar value);
        ColorScalar gamma();
        void process(PixelStrand & strand) override;
    private:
        ColorScalar mGamma;
    };

    class ColorProcessorWhiteBalanced : public ColorProcessor {
    public:
        ColorProcessorWhiteBalanced(const Color & scale);
        void process(PixelStrand & strand) override;
        EIGEN_MAKE_ALIGNED_OPERATOR_NEW
    private:
        Color mScale;
    };

    class ColorProcessorWhiteBalancedGamma : public ColorProcessor {
    public:
        ColorProcessorWhiteBalancedGamma(const Color & scale, ColorScalar gamma);
        void gamma(ColorScalar value);
        ColorScalar gamma();
        void process(PixelStrand & strand) override;
        EIGEN_MAKE_ALIGNED_OPERATOR_NEW
    private:
        Color mScale;
        ColorScalar mGamma;
    };

    class ColorProcessorColorSpace : public ColorProcessor {
    public:
        ColorProcessorColorSpace(const ColorSpace & src, const ColorSpace & dst, const Color & scale);
        void process(PixelStrand & strand) override;
        EIGEN_MAKE_ALIGNED_OPERATOR_NEW
    private:
        ColorSpace::Transformation mTransformation;
    };
}

#endif // COLORPROCESSOR_H
