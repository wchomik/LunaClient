#pragma once

#include <luna/interface/ConnectorPlugin.hpp>

class SecureNetworkConnectorPlugin : public luna::interface::ConnectorPlugin
{
public:
    std::shared_ptr<luna::interface::Connector> createConnector() override;
    QString displayName() const override;
    int displayOrder() const override;
    QUrl itemUrl() const override;
    QObject * model() override;
};
