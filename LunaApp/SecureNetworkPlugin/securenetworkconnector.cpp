#include "securenetworkconnector.h"

#include <QDebug>
#include <QString>

using namespace std::chrono_literals;
using namespace luna;

SecureNetworkConnector::SecureNetworkConnector()
{
    QObject::connect(&mDiscovery, &HostDiscovery::hostDiscovered,
        this, &SecureNetworkConnector::handleHostDiscovered);
}

SecureNetworkConnector::~SecureNetworkConnector() {

}

void SecureNetworkConnector::update() {
    for (auto & host : mHosts) {
        if (host->isConnected()) {
            host->send();
        }
    }
}

void SecureNetworkConnector::getHosts(std::vector<luna::Host *> & hosts) {
    for (auto & host : mHosts) {
        if (host->isConnected()) {
            hosts.emplace_back(host.get());
        }
    }
}

void SecureNetworkConnector::handleHostDiscovered(QHostAddress address) {
    qDebug() << "Found host" << address.toString();
    auto host = std::make_unique<SecureHost>(address);
    mHosts.emplace_back(std::move(host));
}

