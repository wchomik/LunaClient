#ifndef LUNASCREENPROVIDER_H
#define LUNASCREENPROVIDER_H

#include <mutex>
#include "provider.h"
#include "screencapture.h"
#include "config.h"

namespace luna {
    struct ScreenBounds {
        float xLow;
        float xHigh;
        float yLow;
        float yHigh;
    };

    class ScreenProvider : public Provider
    {
    public:
        ScreenProvider();

        void configure(const Config & config) override;
        void setBounds(const ScreenBounds & bounds);
        ColorMode colorMode(class ColorSpace * outColorSpace) override;
        bool getData(std::vector<PixelStrand> & pixelStrands,
                    std::vector<ColorScalar> & whiteStrands) override;

        void setDepth(int depth);
    private slots:
        void onDataReady();
    private:
        void readStrandDimensions();
        void configureScreenCaptureAndMappings();

        graphics::ScreenCapture mScreenCapture;

        struct PixelMapping{
            int startPixel;
            int endPixel;
            int begin;
            int stride;
            int depthStride;
        };

        std::vector<PixelMapping> mMappings;
        Eigen::ArrayXf mDepthWeights;
        int mStrandWidth;
        int mStrandHeight;
        ScreenBounds mBounds;
        Config mLunaConfig;
        std::mutex mMutex;
    public:
        EIGEN_MAKE_ALIGNED_OPERATOR_NEW
    };
}

#endif // LUNASCREENPROVIDER_H
