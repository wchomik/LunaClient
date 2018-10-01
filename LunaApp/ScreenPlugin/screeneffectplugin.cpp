#include "screeneffectplugin.h"

#include "screenprovider.h"

ScreenEffectPlugin::ScreenEffectPlugin() :
    mModel(std::make_unique<ScreenModel>())
{
}

std::shared_ptr<lunacore::Provider> ScreenEffectPlugin::createProvider() {
    auto ret = std::make_shared<ScreenProvider>();
    mModel->provider(ret);
    return ret;
}

QString ScreenEffectPlugin::displayName() const {
    return "Screen";
}

QObject * ScreenEffectPlugin::model() {
    return mModel.get();
}

int ScreenEffectPlugin::displayOrder() const {
    return 50;
}

QUrl ScreenEffectPlugin::itemUrl() const {
    return QUrl("qrc:/Screen/Main.qml");
}
