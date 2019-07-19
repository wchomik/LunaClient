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
    void smoothness(float value);
private:
    void makeDepthWeights();

    ScreenCapture mScreenCapture;
    Array2D<Eigen::Vector4f> mFilteredScreen;

    Eigen::ArrayXf mDepthWeights;
    int mDepth;
    float mBrightness;
    float mGamma;
    float mBlackLevel;
    float mSmoothness;
    std::mutex mMutex;
};
