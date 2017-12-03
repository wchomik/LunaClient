#include "lighttab.h"

#include <luna.h>
#include "lightprovider.h"

LightEffectPlugin::LightEffectPlugin() :
    mModel(std::make_unique<LightModel>())
{
}

LightEffectPlugin::~LightEffectPlugin() {
}

QString LightEffectPlugin::displayName() const {
    return QString("Light");
}

QObject * LightEffectPlugin::model() {
    return mModel.get();
}

int LightEffectPlugin::displayOrder() const {
    return 0;
}

QUrl LightEffectPlugin::itemUrl() const {
    return QUrl("qrc:/LightPlugin.qml");
}


std::shared_ptr<luna::Provider> LightEffectPlugin::createProvider() {
    auto ret = std::shared_ptr<LightProvider>(new LightProvider());
    mModel->provider(ret);
    return ret;
}
