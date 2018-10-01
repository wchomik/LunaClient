#ifndef AUDIOPLUGIN_H
#define AUDIOPLUGIN_H

#include <QObject>

#include <lunaplugin/lunaplugin.h>

class AudioPlugin : public lunacore::LunaPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.luna.audio")
    Q_INTERFACES(lunacore::LunaPlugin)
public:
    QString name() const override;
    void initialize(lunacore::Luna *lunacore) override;
    void finalize(lunacore::Luna *lunacore) override;
};

#endif // AUDIOPLUGIN_H
