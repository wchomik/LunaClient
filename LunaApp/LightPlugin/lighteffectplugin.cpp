#include "lighteffectplugin.h"

#include <lunaplugin/luna.h>
#include "lightprovider.h"

LightEffectPlugin::LightEffectPlugin() :
    mModel(std::make_unique<LightModel>())
{
}

std::shared_ptr<lunacore::Provider> LightEffectPlugin::createProvider() {
    auto ret = std::shared_ptr<LightProvider>(new LightProvider());
    mModel->provider(ret);
    return ret;
}

LightEffectPlugin::~LightEffectPlugin() {
}

QString LightEffectPlugin::displayName() const {
    return "Light";
}

QObject * LightEffectPlugin::model() {
    return mModel.get();
}

int LightEffectPlugin::displayOrder() const {
    return 0;
}

QUrl LightEffectPlugin::itemUrl() const {
    return QUrl("qrc:/Light/Main.qml");
}
