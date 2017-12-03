#include "effectsplugin.h"

#include <luna.h>

#include "flameeffectplugin.h"

void EffectsPlugin::initialize(luna::Luna * luna) {
    luna->addTab(std::make_unique<FlameTab>());
}

void EffectsPlugin::finalize(luna::Luna * luna) {
}

