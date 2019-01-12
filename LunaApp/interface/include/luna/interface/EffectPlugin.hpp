#pragma once

#include "Configurable.hpp"
#include "Provider.hpp"

#include <memory>

namespace luna::interface {
    class EffectPlugin : public Configurable
    {
    public:
        virtual ~EffectPlugin() = default;
        virtual std::shared_ptr<Provider> createProvider() = 0;
    };
}
