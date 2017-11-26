#ifndef COLORPROCESSOR_H
#define COLORPROCESSOR_H

#include "lunacore_global.h"
#include "colorutils.h"
#include "colorspace.h"

namespace luna {
    class LUNACORESHARED_EXPORT ColorProcessor
    {
    public:
        virtual ~ColorProcessor();
        virtual void process(ColorVector & strand) = 0;
    };

    class ColorProcessorDirect : public ColorProcessor {
    public:
        void process(ColorVector & strand) override;
    };

    class ColorProcessorWhiteBalanced : public ColorProcessor {
    public:
        ColorProcessorWhiteBalanced(const Color & scale);
        void process(ColorVector & strand) override;
        EIGEN_MAKE_ALIGNED_OPERATOR_NEW
    private:
        Color mScale;
    };

    class ColorProcessorColorSpace : public ColorProcessor {
    public:
        ColorProcessorColorSpace(const ColorSpace & src, const ColorSpace & dst, const Color & scale);
        void process(ColorVector & strand) override;
        EIGEN_MAKE_ALIGNED_OPERATOR_NEW
    private:
        ColorSpace::Transformation mTransformation;
    };
}

#endif // COLORPROCESSOR_H
