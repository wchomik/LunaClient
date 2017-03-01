#ifndef LUNAMANAGER_H
#define LUNAMANAGER_H

#include <memory>
#include <thread>

#include <Eigen/Core>
#include "connection.h"
#include "colorutils.h"
#include "colormode.h"
#include "colorspace.h"

#include "providerfactory.h"
#include "config.h"

namespace luna {
    class Manager
    {
    public:
        Manager();
        ~Manager();
        Manager(const Manager &) = delete;
        Manager & operator=(const Manager &) = delete;

        Provider * currentProvider();

        void setWhiteBalance(const Color & color);
        void setMode(luna::ProviderType type);

    private:
        void threadFunc();
        void updateColorMode();
        void activateProvider();
        void deactivateProvider();
        void connected();

        // color management
        Color mWhiteBalance;
        ColorSpace mSourceColorSpace;
        ColorSpace mDestinationColorSpace;
        ColorMode mCurrentColorMode;
        std::unique_ptr<class ColorProcessor> mColorProcessor;

        // connection management
        Connection mLuna;

        // provider management
        ProviderFactory mProviderFactory;
        ProviderType mCurrentProviderType;
        std::unique_ptr<class Provider> mActiveProvider;
        Config mLunaConfig;

        std::vector<PixelStrand> mPixelStrands;
        std::vector<ColorScalar> mWhiteStands;

        // concurrency
        bool mShouldRun;
        std::thread mThread;
    public:
        EIGEN_MAKE_ALIGNED_OPERATOR_NEW
    };
}

#endif // LUNAMANAGER_H
