#include "screenplugin.h"

#include <lunaplugin/luna.h>

#include "screeneffectplugin.h"

QString ScreenPlugin::name() const {
    return "Screen";
}

void ScreenPlugin::initialize(lunacore::Luna * luna) {
    luna->addEffect(std::make_unique<ScreenEffectPlugin>());
}

void ScreenPlugin::finalize(lunacore::Luna * luna) {

}
