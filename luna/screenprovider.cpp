#include "screenprovider.h"

#include "config.h"

#include "colorspace.h"

namespace luna {

    ScreenProvider::ScreenProvider(QObject * parent) :
        Provider(parent),
        mScreenCapture(this),
        mBounds{0, 1, 0, 1}
    {
        QObject::connect(&mScreenCapture, &graphics::ScreenCapture::dataReady,
                         this, &ScreenProvider::onDataReady);
        setDepth(20);
    }

    void ScreenProvider::configure(const Config &config)
    {
        Provider::configure(config);
        mLunaConfig = config;
        readStrandDimensions();

        configureScreenCaptureAndMappings();
    }

    void ScreenProvider::setBounds(const ScreenBounds &bounds)
    {
        mBounds = bounds;
        configureScreenCaptureAndMappings();
    }

    ColorMode ScreenProvider::colorMode(ColorSpace * outColorSpace)
    {
        // TODO find a way to read system colorspace
        *outColorSpace = ColorSpace::sRGB();
        return ColorMode::colorSpaceConversion;
    }

    void ScreenProvider::start()
    {
        mScreenCapture.start();
    }

    void ScreenProvider::stop()
    {
        mScreenCapture.stop();
    }

    void ScreenProvider::setDepth(int depth)
    {
        mDepthWeights = Eigen::ArrayXf::LinSpaced(depth, 1.0f, 1.0f / depth);
        mDepthWeights = mDepthWeights / mDepthWeights.sum();
    }

    void ScreenProvider::onDataReady()
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

    void ScreenProvider::readStrandDimensions()
    {
        float width = -1;
        float height = -1;
        for(const auto & strand : mLunaConfig.pixelStrands){
            if(strand.position == Config::bottom ||
                strand.position == Config::top)
            {
                if(-1 == width){
                    width = strand.count;
                }else if(strand.count != width){
                    const char * msg =
                        "Unsupported pixel strand configuration. "
                        "Bottom and top strides must have same pixel count.";
                    throw std::runtime_error(msg);
                }
            }else if(strand.position == Config::left ||
                strand.position == Config::right)
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

    void ScreenProvider::configureScreenCaptureAndMappings()
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
            if(pos == Config::top || pos == Config::bottom){
                pm.stride = colStride;
                pm.depthStride = rowStride;
                if(pos == Config::bottom){
                    pm.begin = rowStride * (height - 1);
                    pm.depthStride *= -1;
                    pm.startPixel = xLow;
                    pm.endPixel = xHigh;
                }
                if(dir == Config::rightToLeft){
                    pm.begin += width - 1;
                    pm.stride *= -1;
                    pm.startPixel = mStrandWidth - xHigh;
                    pm.endPixel = mStrandWidth - xLow;
                }
            }else{
                pm.stride = rowStride;
                pm.depthStride = colStride;
                if(pos == Config::right){
                    pm.begin = width - 1;
                    pm.depthStride *= -1;
                    pm.startPixel = yLow;
                    pm.endPixel = yHigh;
                }
                if(dir == Config::bottomToTop){
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
