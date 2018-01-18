#include "audioplugin.h"

#include <lunaplugin/luna.h>

#include "audioeffectplugin.h"

QString AudioPlugin::name() const {
    return "Audio";
}

void AudioPlugin::initialize(luna::Luna * luna) {
    luna->addEffect(std::make_unique<AudioEffectPlugin>());
}

void AudioPlugin::finalize(luna::Luna * luna) {

}
