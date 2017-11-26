#ifndef LUNAMANAGER_H
#define LUNAMANAGER_H

#include <memory>
#include <thread>
#include <mutex>

#include <Eigen/Core>
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

        Provider * currentProvider(){ return mActiveProvider.get(); }

        void setWhiteBalance(const Color & color);
        void setMode(luna::ProviderType type);
    private:
        void threadFunc();
        void updateColorMode();
        void activateProvider();
        void deactivateProvider();
        void connected();

        // connection management
        std::vector<std::unique_ptr<class Connector>> mConnectors;

        // provider management
        ProviderFactory mProviderFactory;
        ProviderType mCurrentProviderType;
        std::unique_ptr<class Provider> mActiveProvider;

        // concurrency
        bool mShouldRun;
        std::thread mThread;
        std::mutex mMutex;
    public:
        EIGEN_MAKE_ALIGNED_OPERATOR_NEW
    };
}

#endif // LUNAMANAGER_H
