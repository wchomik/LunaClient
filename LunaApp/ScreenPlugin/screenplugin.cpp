#include "screenplugin.h"

#include "screenprovider.h"

ScreenPlugin::ScreenPlugin() :
    mModel(std::make_unique<ScreenModel>())
{
}

ScreenPlugin::~ScreenPlugin() {
}

QString ScreenPlugin::name() const {
    return "Screen";
}

std::shared_ptr<luna::Provider> ScreenPlugin::createProvider() {
    auto ret = std::make_shared<ScreenProvider>();
    mModel->provider(ret);
    return ret;
}

QObject * ScreenPlugin::model() {
    return mModel.get();
}

int ScreenPlugin::displayOrder() const {
    return 50;
}

QUrl ScreenPlugin::itemUrl() {
    return QUrl("qrc:/ScreenPlugin.qml");
}
