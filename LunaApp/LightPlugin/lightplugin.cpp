#include "lightplugin.h"

#include <luna.h>
#include "lighteffectplugin.h"

void LightPlugin::initialize(luna::Luna * luna) {
    luna->addTab(std::make_unique<LightTab>());
}

void LightPlugin::finalize(luna::Luna * luna) {

}
