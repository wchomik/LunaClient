#include "udplegacyconnectorplugin.h"

#include "connectorudplegacy.h"

std::shared_ptr<luna::Connector> UdpLegacyConnectorPlugin::createConnector() {
    auto ret = std::make_shared<ConnectorUDPLegacy>(1234);

    return ret;
}

QString UdpLegacyConnectorPlugin::displayName() const {
    return "Legacy UDP";
}

int UdpLegacyConnectorPlugin::displayOrder() const {
    return 0;
}

QUrl UdpLegacyConnectorPlugin::itemUrl() const {
    return QUrl("qrc:/LegacyUdpPage.qml");
}

QObject * UdpLegacyConnectorPlugin::model() {
    return nullptr;
}
