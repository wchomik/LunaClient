#pragma once

#include "Configurable.hpp"
#include "Connector.hpp"

#include <memory>

namespace luna::interface {
    class ConnectorPlugin : public Configurable
    {
    public:
        virtual std::shared_ptr<Connector> createConnector() = 0;
    };
}
