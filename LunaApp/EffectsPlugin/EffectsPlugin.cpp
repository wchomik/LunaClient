#include "EffectsPlugin.hpp"

#include <luna/interface/Application.hpp>

#include "FlameEffectPlugin.hpp"
#include "PlasmaEffectPlugin.hpp"

std::string EffectsPlugin::name() const {
    return "Effects";
}

void EffectsPlugin::initialize(luna::interface::Application * application) {
    application->addEffect(std::make_unique<FlameEffectPlugin>());
    application->addEffect(std::make_unique<PlasmaEffectPlugin>());
}

void EffectsPlugin::finalize(luna::interface::Application * application) {
}

