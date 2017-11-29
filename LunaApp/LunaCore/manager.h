#ifndef LUNAMANAGER_H
#define LUNAMANAGER_H

#include <memory>
#include <thread>
#include <mutex>

#include <Eigen/Core>


#include "lunacore_global.h"
#include "colorutils.h"
#include "colormode.h"
#include "colorspace.h"
#include "provider.h"

namespace luna {
    class LUNACORESHARED_EXPORT Manager
    {
    public:
        Manager();
        ~Manager();
        Manager(const Manager &) = delete;
        Manager & operator=(const Manager &) = delete;

        void setWhiteBalance(const Color & color);
        void setProvider(std::shared_ptr<Provider> provider);
        void addConnector(std::unique_ptr<class Connector> && connector);
    private:
        void threadFunc();
        void update();
        void updateColorMode();
        void connected();

        std::vector<std::unique_ptr<class Connector>> mConnectors;

        std::shared_ptr<class Provider> mActiveProvider;

        // concurrency
        bool mShouldRun;
        std::thread mThread;
        std::mutex mMutex;
    public:
        EIGEN_MAKE_ALIGNED_OPERATOR_NEW
    };
}

#endif // LUNAMANAGER_H
