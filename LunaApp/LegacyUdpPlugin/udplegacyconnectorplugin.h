#ifndef UDPLEGACYCONNECTORPLUGIN_H
#define UDPLEGACYCONNECTORPLUGIN_H

#include <lunaplugin/connectorplugin.h>

class UdpLegacyConnectorPlugin : public luna::ConnectorPlugin
{
public:
    std::shared_ptr<luna::Connector> createConnector() override;
    QString displayName() const override;
    int displayOrder() const override;
    QUrl itemUrl() const override;
    QObject *model() override;
};

#endif // UDPLEGACYCONNECTORPLUGIN_H
