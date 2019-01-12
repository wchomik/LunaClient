#include "LightPlugin.hpp"

#include "LightEffectPlugin.hpp"

#include <luna/interface/Application.hpp>

std::string LightPlugin::name() const {
    return "Light";
}

void LightPlugin::initialize(luna::interface::Application * application)
{
    application->addEffect(std::make_unique<LightEffectPlugin>());
}

void LightPlugin::finalize(luna::interface::Application * application)
{}
