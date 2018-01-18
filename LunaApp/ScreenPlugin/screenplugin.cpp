#include "screenplugin.h"

#include <lunaplugin/luna.h>

#include "screeneffectplugin.h"

QString ScreenPlugin::name() const {
    return "Screen";
}

void ScreenPlugin::initialize(luna::Luna * luna) {
    luna->addEffect(std::make_unique<ScreenEffectPlugin>());
}

void ScreenPlugin::finalize(luna::Luna * luna) {

}
