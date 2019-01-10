#ifndef LUNASCREENPROVIDER_H
#define LUNASCREENPROVIDER_H

#include <mutex>
#include <luna/interface/provider.h>
#include "screencapture.h"

class ScreenProvider : public luna::interface::Provider
{
public:
    ScreenProvider();

    void getData(std::vector<luna::interface::Strand *> &strands) override;

    void setDepth(int value);
    void setBrightness(luna::interface::ColorScalar value);
    void setGamma(luna::interface::ColorScalar value);
    void setBlackLevel(luna::interface::ColorScalar value);
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
    luna::interface::ColorScalar mBrightness;
    luna::interface::ColorScalar mGamma;
    luna::interface::ColorScalar mBlackLevel;
    std::mutex mMutex;
public:
    EIGEN_MAKE_ALIGNED_OPERATOR_NEW
};


#endif // LUNASCREENPROVIDER_H
