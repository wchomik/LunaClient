#include "Manager.hpp"

#include <luna/interface/Connector.hpp>
#include <luna/interface/Strand.hpp>

#include <QTimer>

#include <chrono>
#include <iostream>

namespace ch = std::chrono;
using namespace std::chrono_literals;
using namespace luna::interface;

Manager::Manager() :
    mShouldRun(true)
{
    QTimer * timer;
    timer = new QTimer();
    timer->setTimerType(Qt::PreciseTimer);
    timer->setInterval(10);
    timer->moveToThread(&mThread);
    QObject::connect(timer, &QTimer::timeout, [this](){ update(); });
    QObject::connect(&mThread, &QThread::started, timer, qOverload<>(&QTimer::start), Qt::DirectConnection);
    QObject::connect(&mThread, &QThread::finished, timer, &QTimer::deleteLater, Qt::DirectConnection);
    mThread.start();
}

Manager::~Manager()
{
    mShouldRun = false;
    mThread.quit();
    mThread.wait();
}

void Manager::postToThread(std::function<void (Manager &)> && message)
{
    std::lock_guard<std::mutex> guard(mMutex);
    mMessages.emplace_back(std::move(message));
}

void Manager::setProvider(std::shared_ptr<Provider> provider)
{
    mActiveProvider = provider;
}

void Manager::addConnector(std::shared_ptr<Connector> connector)
{
    mConnectors.emplace_back(std::move(connector));
}

void Manager::update()
{
    std::lock_guard<std::mutex> guard(mMutex);

    for (auto const & message : mMessages) {
        message(*this);
    }
    mMessages.clear();

    if (nullptr != mActiveProvider) {
        for (auto && connector : mConnectors) {
            auto strands = connector->getStrands();
            for (auto strand : strands) {
                mActiveProvider->getData(*strand);
            }
        }
    }

    for (auto & connector : mConnectors) {
        connector->update();
    }

    if (mActiveProvider) {
        mActiveProvider->update();
    }
}
