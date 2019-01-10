#pragma once

#include "HostDiscovery.hpp"
#include "SecureHost.hpp"

#include <luna/interface/Connector.hpp>

#include <memory>

class SecureNetworkConnector : public QObject, public luna::interface::Connector
{
    Q_OBJECT
public:
    explicit SecureNetworkConnector();
    SecureNetworkConnector(SecureNetworkConnector const &) = delete;
    SecureNetworkConnector & operator=(SecureNetworkConnector const &) = delete;

    void update() override;
    std::vector<luna::interface::Strand *> getStrands() const override;

private slots:
    void onHostDiscovered(QHostAddress address, luna::proto::Discovery const * properties);
    void removeHost(SecureHost * hostToRemove);

private:
    HostDiscovery mDiscovery;
    std::vector<std::unique_ptr<SecureHost>> mHosts;
};
