#include "screenplugin.h"

#include <luna.h>

#include "screentab.h"

void ScreenPlugin::initialize(luna::Luna * luna) {
    luna->addTab(std::make_unique<ScreenTab>());
}

void ScreenPlugin::finalize(luna::Luna * luna) {

}
