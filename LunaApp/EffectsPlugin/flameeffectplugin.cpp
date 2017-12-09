#include "flameeffectplugin.h"

#include "flameprovider.h"
#include "flamemodel.h"

FlameEffectPlugin::FlameEffectPlugin() :
    mModel(std::make_unique<FlameModel>())
{}

std::shared_ptr<luna::Provider> FlameEffectPlugin::createProvider() {
    auto provider = std::shared_ptr<FlameProvider>(new FlameProvider());
    mModel->provider(provider);
    return provider;
}

QString FlameEffectPlugin::displayName() const {
    return QString("Flame");
}

int FlameEffectPlugin::displayOrder() const {
    return 150;
}

QObject * FlameEffectPlugin::model() {
    return mModel.get();
}

QUrl FlameEffectPlugin::itemUrl() const {
    return QUrl("qrc:/FlameTab.qml");
}
