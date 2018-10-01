#ifndef SCREENPLUGIN_H
#define SCREENPLUGIN_H

#include <QObject>

#include <lunaplugin/lunaplugin.h>

class ScreenPlugin : public lunacore::LunaPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.luna.screen")
    Q_INTERFACES(lunacore::LunaPlugin)
public:
    QString name() const override;
    void initialize(lunacore::Luna * lunacore) override;
    void finalize(lunacore::Luna * lunacore) override;
};

#endif // SCREENPLUGIN_H
