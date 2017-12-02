#ifndef CONNECTORPLUGIN_H
#define CONNECTORPLUGIN_H

#include <memory>

#include <QtPlugin>

#include <connector.h>

#include "connectorplugin_global.h"

namespace luna {
    class CONNECTORPLUGINSHARED_EXPORT ConnectorPlugin
    {
    public:
        virtual ~ConnectorPlugin();

        virtual QUrl configurationItemUrl() = 0;
        virtual std::unique_ptr<Connector> createConnector() = 0;
    };
}

Q_DECLARE_INTERFACE(luna::ConnectorPlugin, "org.luna.connector")

#endif // CONNECTORPLUGIN_H
