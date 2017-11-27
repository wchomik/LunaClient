#include "lightplugin.h"

#include "lightprovider.h"

namespace luna {
    LightPlugin::LightPlugin() :
        mModel(std::make_unique<LightModel>())
    {
    }

    LightPlugin::~LightPlugin() {}


    QString LightPlugin::name() {
        return QString("Light");
    }

    std::shared_ptr<luna::Provider> LightPlugin::createProvider() {
        auto ret = std::make_shared<luna::LightProvider>();
        mModel->provider(ret);
        return ret;
    }

    QObject * LightPlugin::model() {
        return mModel.get();
    }

    QUrl LightPlugin::itemUrl() {
        return QUrl("qrc:/LightPlugin.qml");
    }
}
