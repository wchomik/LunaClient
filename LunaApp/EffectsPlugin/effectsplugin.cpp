#include "effectsplugin.h"

#include <luna.h>

#include "flameeffectplugin.h"

void EffectsPlugin::initialize(luna::Luna * luna) {
    luna->addEffect(std::make_unique<FlameEffectPlugin>());
}

void EffectsPlugin::finalize(luna::Luna * luna) {
}

