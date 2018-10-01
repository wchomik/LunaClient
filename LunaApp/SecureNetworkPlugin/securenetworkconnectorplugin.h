#ifndef SECURENETWORKCONNECTORPLUGIN_H
#define SECURENETWORKCONNECTORPLUGIN_H

#include <lunaplugin/connectorplugin.h>

class SecureNetworkConnectorPlugin : public lunacore::ConnectorPlugin
{
public:
    std::shared_ptr<lunacore::Connector> createConnector() override;
    QString displayName() const override;
    int displayOrder() const override;
    QUrl itemUrl() const override;
    QObject * model() override;
};

#endif // SECURENETWORKCONNECTORPLUGIN_H
