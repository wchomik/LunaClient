#include "audioeffectplugin.h"

#include "audioprovider.h"

std::shared_ptr<luna::Provider> AudioEffectPlugin::createProvider() {
    auto ret = std::make_shared<AudioProvider>();
    return ret;
}

QString AudioEffectPlugin::displayName() const {
    return "Audio";
}

QObject * AudioEffectPlugin::model() {
    return mModel.get();
}

int AudioEffectPlugin::displayOrder() const {
    return 100;
}

QUrl AudioEffectPlugin::itemUrl() const {
    return QUrl("qrc:/AudioPlugin.qml");
}
