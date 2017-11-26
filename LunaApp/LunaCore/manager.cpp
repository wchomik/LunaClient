#include "manager.h"

#include <chrono>
#include <iostream>

#include "colorprocessor.h"
#include "connector.h"
#include "connectorudplegacy.h"

#include <qdebug.h>

namespace ch = std::chrono;
using namespace std::chrono_literals;

namespace luna {
    Manager::Manager() :
        mShouldRun(true)
    {
        mConnectors.emplace_back(std::make_unique<ConnectorUDPLegacy>(1234));

        mThread = std::thread([this](){ threadFunc(); });
    }

    Manager::~Manager()
    {
        mShouldRun = false;
        mThread.join();
    }

    void Manager::setWhiteBalance(const Color & color) {
        //std::lock_guard<std::mutex> guard(mMutex);
        //mWhiteBalance = color;
    }

    void Manager::setProvider(std::shared_ptr<Provider> provider)
    {
        std::lock_guard<std::mutex> guard(mMutex);
        mActiveProvider = provider;
    }

    void Manager::threadFunc()
    {
        ch::steady_clock::time_point nextPeriod =
            ch::steady_clock::now() + 10ms;
        while(mShouldRun){
            std::vector<Host *> hosts;
            for (auto && connector : mConnectors) {
                connector->getHosts(hosts);
            }
            std::vector<Strand *> strands;
            for (auto && host : hosts) {
                host->getStrands(strands);
            }
            if (nullptr != mActiveProvider) {
                std::lock_guard<std::mutex> guard(mMutex);
                mActiveProvider->getData(strands);
            }
            for (auto strand : strands) {
                strand->applyColorProcessing();
            }
            for (auto && connector : mConnectors) {
                connector->update();
            }

            auto now = ch::steady_clock::now();
            if(nextPeriod < now)
                nextPeriod = now;
            else while(ch::steady_clock::now() < nextPeriod - 1ms){
                std::this_thread::sleep_until(nextPeriod);
            }

            nextPeriod += 10ms;
        }
    }
}
