#ifndef CONNECTORPLUGIN_H
#define CONNECTORPLUGIN_H

#include <memory>

#include <lunacore/connector.h>

#include "lunaplugin_global.h"

#include "configurableplugin.h"

namespace lunacore {
    class LUNAPLUGINSHARED_EXPORT ConnectorPlugin : public ConfigurablePlugin
    {
    public:
        virtual ~ConnectorPlugin();
        virtual std::shared_ptr<lunacore::Connector> createConnector() = 0;
    };
}

#endif // CONNECTORPLUGIN_H
