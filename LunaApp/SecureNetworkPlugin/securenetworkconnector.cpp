#include "securenetworkconnector.h"

#include <QDebug>
#include <QString>

#include <algorithm>

using namespace std::chrono_literals;
using namespace lunacore;

SecureNetworkConnector::SecureNetworkConnector()
{
    QObject::connect(&mDiscovery, &HostDiscovery::hostDiscovered,
        [this](QHostAddress address) {
            auto const existing = std::find_if(mHosts.begin(), mHosts.end(), [address](auto const & host){ return host->address() == address; });
            if (existing == mHosts.end()) {
                mHosts.emplace_back(std::make_unique<SecureHost>(address));
            }
        });
}

void SecureNetworkConnector::update() {
    for (auto & host : mHosts) {
        if (host->isConnected()) {
            host->send();
        }
    }
}

void SecureNetworkConnector::getHosts(std::vector<lunacore::Host *> & hosts) {
    for (auto & host : mHosts) {
        hosts.emplace_back(host.get());
    }
}

void SecureNetworkConnector::removeHost(SecureHost * hostToRemove)
{
    qDebug() << "Removing";
    auto const existing = std::find_if(mHosts.begin(), mHosts.end(),
        [hostToRemove](auto const & host){ return host.get() == hostToRemove; });

    //mHosts.erase(existing);
}
