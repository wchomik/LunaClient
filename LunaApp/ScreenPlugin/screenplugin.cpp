#include "screenplugin.h"

#include <luna.h>

#include "screeneffectplugin.h"

QString ScreenPlugin::name() const {
    return "Screen";
}

void ScreenPlugin::initialize(luna::Luna * luna) {
    loadTranslation();

    luna->addEffect(std::make_unique<ScreenEffectPlugin>());
}

void ScreenPlugin::finalize(luna::Luna * luna) {
    unloadTranslation();
}
