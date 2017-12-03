#include "screenplugin.h"

#include <luna.h>

#include "screeneffectplugin.h"

void ScreenPlugin::initialize(luna::Luna * luna) {
    luna->addEffect(std::make_unique<ScreenEffectPlugin>());
}

void ScreenPlugin::finalize(luna::Luna * luna) {

}
