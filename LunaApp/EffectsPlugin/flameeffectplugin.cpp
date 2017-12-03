#include "flameeffectplugin.h"

#include "flameprovider.h"

std::shared_ptr<luna::Provider> FlameEffectPlugin::createProvider() {
    auto provider = std::shared_ptr<FlameProvider>(new FlameProvider());
    return provider;
}

QString FlameEffectPlugin::displayName() const {
    return QString("Flame");
}

int FlameEffectPlugin::displayOrder() const {
    return 150;
}

QObject * FlameEffectPlugin::model() {
    return nullptr;
}

QUrl FlameEffectPlugin::itemUrl() const {
    return QUrl("qrc:/FlameTab.qml");
}
