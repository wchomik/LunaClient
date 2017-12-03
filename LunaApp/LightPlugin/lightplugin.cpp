#include "lightplugin.h"

#include <luna.h>
#include "lighteffectplugin.h"

void LightPlugin::initialize(luna::Luna * luna) {
    luna->addEffect(std::make_unique<LightEffectPlugin>());
}

void LightPlugin::finalize(luna::Luna * luna) {

}
