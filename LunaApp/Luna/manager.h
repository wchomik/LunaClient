#ifndef LUNAMANAGER_H
#define LUNAMANAGER_H

#include <memory>
//#include <thread>
#include <QThread>
#include <mutex>
#include <functional>

#include <Eigen/Core>

#include "lunacore_global.h"
#include "colorutils.h"
#include "colormode.h"
#include "colorspace.h"
#include "provider.h"

namespace lunacore {
    class LUNACORESHARED_EXPORT Manager
    {
    public:
        Manager();
        ~Manager();
        Manager(const Manager &) = delete;
        Manager & operator=(const Manager &) = delete;

        void postToThread(std::function<void(Manager & manager)> && message);

        void setProvider(std::shared_ptr<Provider> provider);
        void addConnector(std::shared_ptr<class Connector> connector);
    private:
        void threadFunc();
        void update();
        void updateColorMode();
        void connected();

        std::vector<std::shared_ptr<class Connector>> mConnectors;

        std::shared_ptr<class Provider> mActiveProvider;

        // concurrency
        bool mShouldRun;
//        std::thread mThread;
        QThread mThread;
        std::mutex mMutex;
        std::vector<std::function<void(Manager & manager)>> mMessages;
    public:
        EIGEN_MAKE_ALIGNED_OPERATOR_NEW
    };
}

#endif // LUNAMANAGER_H
