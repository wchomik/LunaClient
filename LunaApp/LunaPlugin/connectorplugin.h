#ifndef CONNECTORPLUGIN_H
#define CONNECTORPLUGIN_H

#include <memory>

#include <connector.h>

#include "lunaplugin_global.h"

#include "configurableplugin.h"

namespace luna {
    class ConnectorPlugin : public ConfigurablePlugin
    {
    public:
        virtual ~ConnectorPlugin();
        virtual std::shared_ptr<luna::Connector> createConnector() = 0;
    };
}

#endif // CONNECTORPLUGIN_H
