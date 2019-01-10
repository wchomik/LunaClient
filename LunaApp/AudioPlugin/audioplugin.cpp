#include "audioplugin.h"

#include <luna/interface/luna.h>

#include "audioeffectplugin.h"

QString AudioPlugin::name() const {
    return "Audio";
}

void AudioPlugin::initialize(luna::interface::Luna * luna) {
    luna->addEffect(std::make_unique<AudioEffectPlugin>());
}

void AudioPlugin::finalize(luna::interface::Luna * luna) {

}
