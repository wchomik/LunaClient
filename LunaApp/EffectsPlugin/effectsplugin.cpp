#include "effectsplugin.h"

#include <luna.h>

#include "flameeffectplugin.h"
#include "plasmaeffectplugin.h"

QString EffectsPlugin::name() const {
    return "Effects";
}

void EffectsPlugin::initialize(luna::Luna * luna) {
    luna->addEffect(std::make_unique<FlameEffectPlugin>());
    luna->addEffect(std::make_unique<PlasmaEffectPlugin>());
}

void EffectsPlugin::finalize(luna::Luna * luna) {
}

