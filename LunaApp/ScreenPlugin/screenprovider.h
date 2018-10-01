#ifndef LUNASCREENPROVIDER_H
#define LUNASCREENPROVIDER_H

#include <mutex>
#include <lunacore/provider.h>
#include "screencapture.h"

class ScreenProvider : public lunacore::Provider
{
public:
    ScreenProvider();

    void getData(std::vector<lunacore::Strand *> &strands) override;

    void setDepth(int value);
    void setBrightness(lunacore::ColorScalar value);
    void setGamma(lunacore::ColorScalar value);
    void setBlackLevel(lunacore::ColorScalar value);
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
    lunacore::ColorScalar mBrightness;
    lunacore::ColorScalar mGamma;
    lunacore::ColorScalar mBlackLevel;
    std::mutex mMutex;
public:
    EIGEN_MAKE_ALIGNED_OPERATOR_NEW
};


#endif // LUNASCREENPROVIDER_H
