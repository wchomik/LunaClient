#pragma once

#include "Configurable.hpp"

#include <lunacore/connector.h>

#include <memory>

namespace lunacore {
    class ConnectorPlugin : public ConfigurablePlugin
    {
    public:
        virtual std::shared_ptr<lunacore::Connector> createConnector() = 0;
    };
}
