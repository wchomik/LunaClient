#ifndef AUDIOPLUGIN_H
#define AUDIOPLUGIN_H

#include <QObject>

#include <luna/interface/lunaplugin.h>

class AudioPlugin : public luna::interface::LunaPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.luna.audio")
    Q_INTERFACES(luna::interface::LunaPlugin)
public:
    QString name() const override;
    void initialize(luna::interface::Luna *lunacore) override;
    void finalize(luna::interface::Luna *lunacore) override;
};

#endif // AUDIOPLUGIN_H
