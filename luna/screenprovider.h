#ifndef LUNASCREENPROVIDER_H
#define LUNASCREENPROVIDER_H

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
        explicit ScreenProvider(QObject * parent = nullptr);

        void configure(const Config & config) override;
        void setBounds(const ScreenBounds & bounds);
        ColorMode colorMode(class ColorSpace * outColorSpace) override;

        void start() override;
        void stop() override;

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
    };
}

#endif // LUNASCREENPROVIDER_H
