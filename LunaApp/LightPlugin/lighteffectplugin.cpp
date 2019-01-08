#include "LightEffectPlugin.hpp"

#include "LightProvider.hpp"

#include <luna/interface/Application.hpp>

LightEffectPlugin::LightEffectPlugin() :
    mModel(std::make_unique<LightModel>())
{
}

std::shared_ptr<luna::interface::Provider> LightEffectPlugin::createProvider() {
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
