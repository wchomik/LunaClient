#include "screenplugin.h"

#include <luna/interface/luna.h>

#include "screeneffectplugin.h"

QString ScreenPlugin::name() const {
    return "Screen";
}

void ScreenPlugin::initialize(luna::interface::Luna * luna) {
    luna->addEffect(std::make_unique<ScreenEffectPlugin>());
}

void ScreenPlugin::finalize(luna::interface::Luna * luna) {

}
