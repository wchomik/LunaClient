#include "lighttab.h"

#include <luna.h>
#include "lightprovider.h"

LightTab::LightTab() :
    mModel(std::make_unique<LightModel>())
{
}

LightTab::~LightTab() {
}

void LightTab::activate(luna::Luna * application) {
    auto ret = std::shared_ptr<LightProvider>(new LightProvider());
    mModel->provider(ret);
    application->manager().setProvider(ret);
}

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

