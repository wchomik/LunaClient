#ifndef STRAND_H
#define STRAND_H

#include <vector>
#include <memory>
#include <cstdint>

#include "lunacore_global.h"
#include "colormode.h"
#include "colorutils.h"
#include "colorspace.h"
#include "colorprocessor.h"

namespace luna {
    enum ColorChannels : uint32_t {
        red = 1 << 0,
        green = 1 << 1,
        blue = 1 << 2,
        white = 1 << 3,
        rgb = red | green | blue,
    };

    class LUNACORESHARED_EXPORT Strand
    {
    public:
        struct LUNACORESHARED_EXPORT Config {
            ColorSpace colorSpace;
            ColorChannels colorChannels;
            uint32_t count;
            Eigen::Vector3f begin;
            Eigen::Vector3f end;

            EIGEN_MAKE_ALIGNED_OPERATOR_NEW
        };
        Strand(const Config & config);

        const Config & config() const;
        Color * pixels();
        Eigen::Vector3f positionOf(unsigned index);

        void applyColorProcessing();

        void setDirectColorMode();
        void setSpaceConversionColorMode(const ColorSpace & sourceColorSpace);
        void setAll(const Color & color);
    private:
        Config mConfig;
        ColorVector mPixels;
        std::unique_ptr<ColorProcessor> mColorProcessor;
        float mPositionInterpolationFactor;
    public:
        EIGEN_MAKE_ALIGNED_OPERATOR_NEW
    };

    template<typename T>
    class StrandData {
    public:
        T & operator[](Strand * key) {
            auto it = mStorage.find(key);
            if (mStorage.end() == it) {
                it = mStorage.emplace(std::make_pair(key, T(key))).first;
            }
            return it->second;
        }
    private:
        aligned_unordered_map<Strand *, T> mStorage;
    };
}

#endif // STRAND_H
