#include "ScreenPlugin.hpp"

#include "ScreenEffectPlugin.hpp"

#include <luna/interface/Application.hpp>

std::string ScreenPlugin::name() const
{
    return "Screen";
}

void ScreenPlugin::initialize(luna::interface::Application * application)
{
    application->addEffect(std::make_unique<ScreenEffectPlugin>());
}

void ScreenPlugin::finalize(luna::interface::Application * application)
{}
