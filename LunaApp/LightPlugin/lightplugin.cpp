#include "lightplugin.h"

#include <lunaplugin/luna.h>
#include "lighteffectplugin.h"

QString LightPlugin::name() const {
    return "Light";
}

void LightPlugin::initialize(lunacore::Luna * luna) {
    luna->addEffect(std::make_unique<LightEffectPlugin>());
}

void LightPlugin::finalize(lunacore::Luna * luna) {

}
