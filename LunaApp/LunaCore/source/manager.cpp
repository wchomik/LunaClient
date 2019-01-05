#include "manager.h"

#include <chrono>
#include <iostream>

#include "colorprocessor.h"
#include "connector.h"
#include "strand.h"

#include <QDebug>
#include <QTimer>

namespace ch = std::chrono;
using namespace std::chrono_literals;

namespace lunacore {
    Manager::Manager() :
        mShouldRun(true)
    {
//        mThread = std::thread([this]() {
//            threadFunc();
//        });
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

    Manager::~Manager() {
        mShouldRun = false;
        mThread.quit();
        mThread.wait();
//        mThread.join();
    }

    void Manager::postToThread(std::function<void (Manager &)> && message)
    {
        std::lock_guard<std::mutex> guard(mMutex);
        mMessages.emplace_back(std::move(message));
    }

    void Manager::setProvider(std::shared_ptr<Provider> provider) {
        mActiveProvider = provider;
    }

    void Manager::addConnector(std::shared_ptr<Connector> connector) {
        mConnectors.emplace_back(std::move(connector));
    }

    void Manager::threadFunc() {
        ch::steady_clock::time_point nextPeriod =
            ch::steady_clock::now() + 10ms;
        while (mShouldRun) {
            update();

            auto now = ch::steady_clock::now();
            if (nextPeriod < now) {
                nextPeriod = now;
            } else while (ch::steady_clock::now() < nextPeriod - 1ms) {
                std::this_thread::sleep_until(nextPeriod);
            }

            nextPeriod += 10ms;
        }
    }

    void Manager::update() {
        std::vector<Host *> hosts;
        std::lock_guard<std::mutex> guard(mMutex);

        for (auto const & message : mMessages) {
            message(*this);
        }
        mMessages.clear();

        for (auto && connector : mConnectors) {
            connector->getHosts(hosts);
        }
        std::vector<Strand *> strands;
        for (auto && host : hosts) {
            host->getStrands(strands);
        }

        if (nullptr != mActiveProvider) {
            mActiveProvider->getData(strands);
        }
        for (auto strand : strands) {
            strand->applyColorProcessing();
        }
        for (auto && connector : mConnectors) {
            connector->update();
        }
    }
}
