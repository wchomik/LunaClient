#pragma once

#include <memory>

namespace luna::interface {
    class EffectPlugin;
    class ConnectorPlugin;

    class Application
    {
    public:
        virtual ~Application() = default;
        virtual void addEffect(std::unique_ptr<EffectPlugin> && effect) = 0;
        virtual void addConnector(std::unique_ptr<ConnectorPlugin> && connector) = 0;
    };
}