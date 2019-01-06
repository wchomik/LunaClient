#pragma once

#include "Configurable.h"

#include <lunacore/provider.h>

#include <memory>

namespace lunacore {
    class EffectPlugin : public ConfigurablePlugin
    {
    public:
        virtual ~EffectPlugin() = default;
        virtual std::shared_ptr<lunacore::Provider> createProvider() = 0;
    };
}
