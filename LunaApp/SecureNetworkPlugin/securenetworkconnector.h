#pragma once

#include "hostdiscovery.h"
#include "securehost.h"

#include <lunacore/connector.h>

#include <memory>

class SecureNetworkConnector : public lunacore::Connector
{
public:
    explicit SecureNetworkConnector();
    SecureNetworkConnector(SecureNetworkConnector const &) = delete;
    SecureNetworkConnector & operator=(SecureNetworkConnector const &) = delete;

    void update() override;
    void getHosts(std::vector<lunacore::Host *> & hosts) override;
private:
    void removeHost(SecureHost * hostToRemove);

    HostDiscovery mDiscovery;
    std::vector<std::unique_ptr<SecureHost>> mHosts;
};
