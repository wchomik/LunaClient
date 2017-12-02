#ifndef AUDIOPLUGIN_H
#define AUDIOPLUGIN_H

#include <QObject>

#include <lunaplugin.h>

class AudioPlugin : public QObject, public luna::LunaPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.luna.audio")
    Q_INTERFACES(luna::LunaPlugin)
public:
    void initialize(luna::Luna *luna) override;
    void finalize(luna::Luna *luna) override;
};

#endif // AUDIOPLUGIN_H
