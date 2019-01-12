#include "AudioPlugin.hpp"

#include "AudioEffectPlugin.hpp"

#include <luna/interface/Application.hpp>

std::string AudioPlugin::name() const {
    return "Audio";
}

void AudioPlugin::initialize(luna::interface::Application * application) {
    application->addEffect(std::make_unique<AudioEffectPlugin>());
}

void AudioPlugin::finalize(luna::interface::Application * application) {

}
