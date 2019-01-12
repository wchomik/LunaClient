#include "PlasmaEffectPlugin.hpp"

#include "PlasmaProvider.hpp"

PlasmaEffectPlugin::PlasmaEffectPlugin() :
    mModel(std::make_unique<PlasmaModel>())
{}

QString PlasmaEffectPlugin::displayName() const
{
    return "Plasma";
}

int PlasmaEffectPlugin::displayOrder() const
{
    return 200;
}

QUrl PlasmaEffectPlugin::itemUrl() const
{
    return QUrl("qrc:/Effects/PlasmaTab.qml");
}

QObject * PlasmaEffectPlugin::model()
{
    return mModel.get();
}

std::shared_ptr<luna::interface::Provider> PlasmaEffectPlugin::createProvider()
{
    return std::make_shared<PlasmaProvider>();
}
