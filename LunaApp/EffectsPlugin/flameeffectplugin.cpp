#include "flameeffectplugin.h"

#include "flameprovider.h"

void FlameTab::activate(luna::Manager * manager) {
    auto provider = std::shared_ptr<FlameProvider>(new FlameProvider());

    manager->setProvider(provider);
}

void FlameTab::deactivate(luna::Manager * manager) {

}

QString FlameTab::displayName() const {
    return QString("Flame");
}

int FlameTab::displayOrder() const {
    return 150;
}

QObject * FlameTab::model() {
    return nullptr;
}

QUrl FlameTab::itemUrl() const {
    return QUrl("qrc:/FlameTab.qml");
}
