#ifndef LIGHTPLUGIN_H
#define LIGHTPLUGIN_H

#include <QObject>

#include <lunaplugin/lunaplugin.h>

class LightPlugin : public luna::LunaPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.luna.light")
    Q_INTERFACES(luna::LunaPlugin)
public:
    QString name() const override;
    void initialize(luna::Luna *luna) override;
    void finalize(luna::Luna *luna) override;
};

#endif // LIGHTPLUGIN_H
