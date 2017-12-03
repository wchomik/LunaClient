#include "audioplugin.h"

#include <luna.h>

#include "audioeffectplugin.h"

void AudioPlugin::initialize(luna::Luna * luna) {
    luna->addTab(std::make_unique<AudioTab>());
}

void AudioPlugin::finalize(luna::Luna * luna) {

}
