#include "audiotab.h"

#include "audioprovider.h"

void AudioTab::activate(luna::Manager * manager) {
    auto ret = std::make_shared<AudioProvider>();
    manager->setProvider(ret);
}

void AudioTab::deactivate(luna::Manager * manager) {

}

QString AudioTab::displayName() const {
    return "Audio";
}

QObject * AudioTab::model() {
    return mModel.get();
}

int AudioTab::displayOrder() const {
    return 100;
}

QUrl AudioTab::itemUrl() const {
    return QUrl("qrc:/AudioPlugin.qml");
}
