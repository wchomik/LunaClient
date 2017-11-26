#include "lightplugin.h"


LightPlugin::LightPlugin()
{
}


QString LightPlugin::name() {
    return QString("Light");
}

/*QQuickItem * LightPlugin::createItem() {
    return nullptr;
}*/

std::unique_ptr<luna::Provider> LightPlugin::createProvider() {
    return nullptr;
}
