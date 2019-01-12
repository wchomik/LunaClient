#include "FlameEffectPlugin.hpp"

#include "FlameProvider.hpp"
#include "FlameModel.hpp"

FlameEffectPlugin::FlameEffectPlugin() :
    mModel(std::make_unique<FlameModel>())
{}

std::shared_ptr<luna::interface::Provider> FlameEffectPlugin::createProvider() {
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
    return QUrl("qrc:/Effects/FlameTab.qml");
}
