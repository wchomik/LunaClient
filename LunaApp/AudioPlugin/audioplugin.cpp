#include "audioplugin.h"

#include <lunaplugin/luna.h>

#include "audioeffectplugin.h"

QString AudioPlugin::name() const {
    return "Audio";
}

void AudioPlugin::initialize(lunacore::Luna * luna) {
    luna->addEffect(std::make_unique<AudioEffectPlugin>());
}

void AudioPlugin::finalize(lunacore::Luna * luna) {

}
