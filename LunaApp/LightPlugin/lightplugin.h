#ifndef LIGHTPLUGIN_H
#define LIGHTPLUGIN_H

#include <QObject>
#include <lunaplugin.h>

class LightPlugin : public QObject, public luna::LunaPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID LunaPlugin_iid)
    Q_INTERFACES(luna::LunaPlugin)
public:
    LightPlugin();
    QString name() override;
    //QQuickItem * createItem() override;
    std::unique_ptr<luna::Provider> createProvider() override;
};

#endif // LIGHTPLUGIN_H
