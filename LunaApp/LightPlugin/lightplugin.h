#ifndef LIGHTPLUGIN_H
#define LIGHTPLUGIN_H

#include <QObject>

#include <lunaplugin/lunaplugin.h>

class LightPlugin : public lunacore::LunaPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.luna.light")
    Q_INTERFACES(lunacore::LunaPlugin)
public:
    QString name() const override;
    void initialize(lunacore::Luna *lunacore) override;
    void finalize(lunacore::Luna *lunacore) override;
};

#endif // LIGHTPLUGIN_H
