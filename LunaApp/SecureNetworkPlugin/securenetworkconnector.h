#pragma once

#include "hostdiscovery.h"
#include "securehost.h"

#include <lunacore/connector.h>

#include <QObject>
#include <memory>

class SecureNetworkConnector : public QObject, public luna::Connector
{
    Q_OBJECT
public:
    explicit SecureNetworkConnector();
    ~SecureNetworkConnector() override;
    SecureNetworkConnector(SecureNetworkConnector const &) = delete;
    SecureNetworkConnector & operator=(SecureNetworkConnector const &) = delete;
    void update() override;
    void getHosts(std::vector<luna::Host *> & hosts) override;
private slots:
    void handleHostDiscovered(QHostAddress address);
private:
    void updateHosts();
    void onHostConnected();

    HostDiscovery mDiscovery;
    std::vector<std::unique_ptr<SecureHost>> mHosts;
};
