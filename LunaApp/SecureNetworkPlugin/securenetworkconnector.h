#pragma once

#include "hostdiscovery.h"
#include "securehost.h"

#include <lunacore/connector.h>

#include <memory>

class SecureNetworkConnector : public QObject, public lunacore::Connector
{
    Q_OBJECT
public:
    explicit SecureNetworkConnector();
    SecureNetworkConnector(SecureNetworkConnector const &) = delete;
    SecureNetworkConnector & operator=(SecureNetworkConnector const &) = delete;

    void update() override;
    void getHosts(std::vector<lunacore::Host *> & hosts) override;
private slots:
    void onHostDiscovered(QHostAddress address, luna::proto::Discovery const * properties);
    void removeHost(SecureHost * hostToRemove);
private:

    HostDiscovery mDiscovery;
    std::vector<std::unique_ptr<SecureHost>> mHosts;
};
