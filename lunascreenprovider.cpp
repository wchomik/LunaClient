#include "lunascreenprovider.h"

#include "lunaconfig.h"

#include "colorspace.h"

namespace luna {

    LunaScreenProvider::LunaScreenProvider(QObject * parent) :
        LunaProvider(parent),
        mScreenCapture(this),
        mBounds{0, 1, 0, 1}
    {
        QObject::connect(&mScreenCapture, &graphics::ScreenCapture::dataReady,
                         this, &LunaScreenProvider::onDataReady);
        setDepth(20);
    }

    void LunaScreenProvider::configure(const LunaConfig &config)
    {
        LunaProvider::configure(config);
        mLunaConfig = config;
        readStrandDimensions();

        configureScreenCaptureAndMappings();
    }

    void LunaScreenProvider::setBounds(const ScreenBounds &bounds)
    {
        mBounds = bounds;
        configureScreenCaptureAndMappings();
    }

    ColorMode LunaScreenProvider::colorMode(ColorSpace * outColorSpace)
    {
        // TODO find a way to read system colorspace
        *outColorSpace = ColorSpace::sRGB();
        return ColorMode::colorSpaceConversion;
    }

    void LunaScreenProvider::start()
    {
        mScreenCapture.start();
    }

    void LunaScreenProvider::stop()
    {
        mScreenCapture.stop();
    }

    void LunaScreenProvider::setDepth(int depth)
    {
        mDepthWeights = Eigen::ArrayXf::LinSpaced(depth, 1.0f, 1.0f / depth);
        mDepthWeights = mDepthWeights / mDepthWeights.sum();
    }

    void LunaScreenProvider::onDataReady()
    {
        Color * pixels = mScreenCapture.pixels().data();
        const int depth = mDepthWeights.rows();
        for(int i = 0; i < mMappings.size(); ++i){
            PixelStrand & strand = mPixelStrands[i];
            const PixelMapping & mapping = mMappings[i];
            const int count = strand.size();
            for(int x = mapping.startPixel; x < mapping.endPixel; ++x){
                Color color(0, 0, 0, 0);
                for(int d = 0; d < depth; ++d){
                    int index = mapping.begin +
                                x * mapping.stride +
                                d * mapping.depthStride;
                    color += pixels[index] * mDepthWeights[d];
                }
                strand[x] = color;
            }
        }

        emit dataReady();
    }

    void LunaScreenProvider::readStrandDimensions()
    {
        float width = -1;
        float height = -1;
        for(const auto & strand : mLunaConfig.pixelStrands){
            if(strand.position == LunaConfig::bottom ||
                strand.position == LunaConfig::top)
            {
                if(-1 == width){
                    width = strand.count;
                }else if(strand.count != width){
                    const char * msg =
                        "Unsupported pixel strand configuration. "
                        "Bottom and top strides must have same pixel count.";
                    throw std::runtime_error(msg);
                }
            }else if(strand.position == LunaConfig::left ||
                strand.position == LunaConfig::right)
            {
                if(-1 == height){
                    height = strand.count;
                }else if(strand.count != height){
                    const char * msg =
                        "Unsupported pixel strand configuration. "
                        "Left and right strides must have same pixel count.";
                    throw std::runtime_error(msg);
                }
            }
        }

        if(-1 == width && -1 == height){
            throw std::runtime_error("No pixel strands found. I don't know what to do.");
        }

        if(-1 == width){
            // without actually capturing the screen it's impossible to get aspect ratio
            // so we assume 16/9 ratio
            width = height * 16 / 9;
        }else if(-1 == height){
            height = width * 9 / 16;
        }

        mStrandWidth = width;
        mStrandHeight = height;
    }

    void LunaScreenProvider::configureScreenCaptureAndMappings()
    {
        const int width = mStrandWidth * (mBounds.xHigh - mBounds.xLow);
        const int height = mStrandHeight * (mBounds.yHigh - mBounds.yLow);

        const int xLow = std::lround(mStrandWidth * mBounds.xLow);
        const int xHigh = std::lround(mStrandWidth * mBounds.xHigh);
        const int yLow = std::lround(mStrandHeight * mBounds.yLow);
        const int yHigh = std::lround(mStrandHeight * mBounds.yHigh);

        const int colStride = 1;
        const int rowStride = width;


        mScreenCapture.configure(width, height);

        mMappings.clear();
        for(const auto & strand : mLunaConfig.pixelStrands){
            const auto pos = strand.position;
            const auto dir = strand.direction;
            PixelMapping pm{0, 0, 0, 0, 0};
            if(pos == LunaConfig::top || pos == LunaConfig::bottom){
                pm.stride = colStride;
                pm.depthStride = rowStride;
                if(pos == LunaConfig::bottom){
                    pm.begin = rowStride * (height - 1);
                    pm.depthStride *= -1;
                    pm.startPixel = xLow;
                    pm.endPixel = xHigh;
                }
                if(dir == LunaConfig::rightToLeft){
                    pm.begin += width - 1;
                    pm.stride *= -1;
                    pm.startPixel = mStrandWidth - xHigh;
                    pm.endPixel = mStrandWidth - xLow;
                }
            }else{
                pm.stride = rowStride;
                pm.depthStride = colStride;
                if(pos == LunaConfig::right){
                    pm.begin = width - 1;
                    pm.depthStride *= -1;
                    pm.startPixel = yLow;
                    pm.endPixel = yHigh;
                }
                if(dir == LunaConfig::bottomToTop){
                    pm.begin += rowStride * (height - 1);
                    pm.stride *= -1;
                    pm.startPixel = mStrandHeight - yHigh;
                    pm.endPixel = mStrandHeight - yLow;
                }
            }
            pm.begin -= pm.startPixel * pm.stride;
            mMappings.push_back(pm);
        }
    }

}
