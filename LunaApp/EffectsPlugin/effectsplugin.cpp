#include "effectsplugin.h"

#include <lunaplugin/luna.h>

#include "flameeffectplugin.h"
#include "plasmaeffectplugin.h"

QString EffectsPlugin::name() const {
    return "Effects";
}

void EffectsPlugin::initialize(lunacore::Luna * luna) {
    luna->addEffect(std::make_unique<FlameEffectPlugin>());
    luna->addEffect(std::make_unique<PlasmaEffectPlugin>());
}

void EffectsPlugin::finalize(lunacore::Luna * luna) {
}

