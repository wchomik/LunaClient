#pragma once


#include <luna/interface/Provider.hpp>
#include <luna/interface/Connector.hpp>

#include <QThread>

#include <memory>
#include <mutex>
#include <functional>

class Manager
{
public:
    explicit Manager();
    ~Manager();
    Manager(const Manager &) = delete;
    Manager & operator=(const Manager &) = delete;

    void postToThread(std::function<void(Manager & manager)> && message);

    void setProvider(std::shared_ptr<luna::interface::Provider> provider);
    void addConnector(std::shared_ptr<luna::interface::Connector> connector);
private:
    void threadFunc();
    void update();
    void updateColorMode();
    void connected();

    std::vector<std::shared_ptr<luna::interface::Connector>> mConnectors;

    std::shared_ptr<luna::interface::Provider> mActiveProvider;

    bool mShouldRun;
    QThread mThread;
    std::mutex mMutex;
    std::vector<std::function<void(Manager & manager)>> mMessages;
};
