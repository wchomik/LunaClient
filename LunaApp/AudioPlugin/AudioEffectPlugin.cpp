#include "AudioEffectPlugin.hpp"

#include "AudioProvider.hpp"

std::shared_ptr<luna::interface::Provider> AudioEffectPlugin::createProvider()
{
    auto ret = std::make_shared<AudioProvider>();
    return ret;
}

QString AudioEffectPlugin::displayName() const
{
    return "Audio";
}

QObject * AudioEffectPlugin::model()
{
    return mModel.get();
}

int AudioEffectPlugin::displayOrder() const
{
    return 100;
}

QUrl AudioEffectPlugin::itemUrl() const
{
    return QUrl("qrc:/Audio/Main.qml");
}
