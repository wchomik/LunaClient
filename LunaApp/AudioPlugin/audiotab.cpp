#include "audiotab.h"

#include "audioprovider.h"

AudioPlugin::AudioPlugin() {}

AudioPlugin::~AudioPlugin() {}

QString AudioPlugin::name() const {
    return "Audio";
}

std::shared_ptr<luna::Provider> AudioPlugin::createProvider() {
    auto ret = std::make_shared<AudioProvider>();

    return ret;
}

QObject * AudioPlugin::model() {
    return nullptr;
}

int AudioPlugin::displayOrder() const {
    return 100;
}

QUrl AudioPlugin::itemUrl() {
    return QUrl("qrc:/AudioPlugin.qml");
}
