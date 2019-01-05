#include "securenetworkconnector.h"

#include <QDebug>
#include <QString>
#include <QHostAddress>

#include <algorithm>

using namespace std::chrono_literals;
using namespace lunacore;

SecureNetworkConnector::SecureNetworkConnector()
{
    QObject::connect(
        &mDiscovery, &HostDiscovery::hostDiscovered,
        this, &SecureNetworkConnector::onHostDiscovered);
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

void SecureNetworkConnector::onHostDiscovered(QHostAddress address, luna::proto::Discovery const * properties)
{
    auto const existing = std::find_if(mHosts.begin(), mHosts.end(),
        [address](auto const & host){ return host->address().isEqual(address, QHostAddress::TolerantConversion); }
    );

    if (existing == mHosts.end()) {
        mHosts.emplace_back(std::make_unique<SecureHost>(address, properties));
        auto & host = mHosts.back();
        QObject::connect(host.get(), &SecureHost::disconnected,
            [this, host = host.get()](){
                removeHost(host);
            }
        );
    }
}

void SecureNetworkConnector::removeHost(SecureHost * hostToRemove)
{
    qDebug() << "Removing";
    auto const existing = std::find_if(mHosts.begin(), mHosts.end(),
        [hostToRemove](auto const & host){ return host.get() == hostToRemove; });

    mHosts.erase(existing);
}
