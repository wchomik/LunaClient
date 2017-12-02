#include "lighttab.h"

#include <luna.h>
#include "lightprovider.h"

LightTab::LightTab() :
    mModel(std::make_unique<LightModel>())
{
}

LightTab::~LightTab() {
}

void LightTab::activate(luna::Manager * manager) {
    auto ret = std::shared_ptr<LightProvider>(new LightProvider());
    mModel->provider(ret);
    manager->setProvider(ret);
}

void LightTab::deactivate(luna::Manager * manager) { }

QString LightTab::displayName() const {
    return QString("Light");
}

QObject * LightTab::model() {
    return mModel.get();
}

int LightTab::displayOrder() const {
    return 0;
}

QUrl LightTab::itemUrl() const {
    return QUrl("qrc:/LightPlugin.qml");
}

