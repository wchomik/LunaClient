#ifndef LUNASCREENPROVIDER_H
#define LUNASCREENPROVIDER_H

#include <mutex>
#include <lunacore/provider.h>
#include "screencapture.h"

class ScreenProvider : public luna::Provider
{
public:
    ScreenProvider();

    void getData(std::vector<luna::Strand *> &strands) override;

    void setDepth(int value);
    void setBrightness(luna::ColorScalar value);
    void setGamma(luna::ColorScalar value);
    void setBlackLevel(luna::ColorScalar value);
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
    luna::ColorScalar mBrightness;
    luna::ColorScalar mGamma;
    luna::ColorScalar mBlackLevel;
    std::mutex mMutex;
public:
    EIGEN_MAKE_ALIGNED_OPERATOR_NEW
};


#endif // LUNASCREENPROVIDER_H
