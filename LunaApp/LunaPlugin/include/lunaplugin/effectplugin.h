#ifndef EFFECTPLUGIN_H
#define EFFECTPLUGIN_H

#include <memory>

#include <lunacore/provider.h>

#include "lunaplugin_global.h"
#include "configurableplugin.h"

namespace lunacore {
    class LUNAPLUGINSHARED_EXPORT EffectPlugin : public ConfigurablePlugin
    {
    public:
        virtual ~EffectPlugin();
        virtual std::shared_ptr<lunacore::Provider> createProvider() = 0;
    };
}

#endif // EFFECTPLUGIN_H
