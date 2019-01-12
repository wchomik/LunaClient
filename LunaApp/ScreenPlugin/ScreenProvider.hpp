#pragma once

#include "ScreenCapture.hpp"

#include <luna/interface/Provider.hpp>

#include <Eigen/Dense>
#include <vector>
#include <mutex>

class ScreenProvider : public luna::interface::Provider
{
public:
    explicit ScreenProvider();

    void getData(luna::interface::Strand & strand) override;
    void update() override;

    void setDepth(int value);
    void setBrightness(float value);
    void setGamma(float value);
    void setBlackLevel(float value);
private:
    void makeDepthWeights();

    ScreenCapture mScreenCapture;

    struct PixelMapping{
        int startPixel;
        int endPixel;
        int begin;
        int stride;
        int depthStride;
    };

    std::vector<PixelMapping> mMappings;
    Eigen::ArrayXf mDepthWeights;
    int mDepth;
    float mBrightness;
    float mGamma;
    float mBlackLevel;
    std::mutex mMutex;
};
