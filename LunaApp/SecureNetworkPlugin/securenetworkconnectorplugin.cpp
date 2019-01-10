#include "SecureNetworkConnectorPlugin.hpp"

#include "SecureNetworkConnector.hpp"

std::shared_ptr<luna::interface::Connector> SecureNetworkConnectorPlugin::createConnector() {
    return std::make_shared<SecureNetworkConnector>();
}

QString SecureNetworkConnectorPlugin::displayName() const {
    return "Secure Network";
}

int SecureNetworkConnectorPlugin::displayOrder() const {
    return 1;
}

QUrl SecureNetworkConnectorPlugin::itemUrl() const {
    return QUrl("qrc:/SecureNetwork/SecureNetworkPage.qml");
}

QObject * SecureNetworkConnectorPlugin::model() {
    return nullptr;
}
