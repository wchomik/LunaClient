#include "manager.h"

#include <chrono>
#include <iostream>

#include "colorprocessor.h"
#include "connector.h"
#include "strand.h"

#include <QDebug>

namespace ch = std::chrono;
using namespace std::chrono_literals;

namespace luna {
    Manager::Manager() :
        mShouldRun(true)
    {
        mThread = std::thread([this]() {
            threadFunc();
        });
    }

    Manager::~Manager() {
        mShouldRun = false;
        mThread.join();
    }

    void Manager::setProvider(std::shared_ptr<Provider> provider) {
        std::lock_guard<std::mutex> guard(mMutex);
        mActiveProvider = provider;
    }

    void Manager::addConnector(std::shared_ptr<Connector> connector) {
        std::lock_guard<std::mutex> guard(mMutex);
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
        for (auto && connector : mConnectors) {
            connector->getHosts(hosts);
        }
        std::vector<Strand *> strands;
        for (auto && host : hosts) {
            host->getStrands(strands);
        }
        //qDebug() << strands.size() << "Strands";
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
