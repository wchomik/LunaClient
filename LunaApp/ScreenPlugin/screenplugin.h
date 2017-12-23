#ifndef SCREENPLUGIN_H
#define SCREENPLUGIN_H

#include <QObject>

#include <lunaplugin.h>

class ScreenPlugin : public luna::LunaPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.luna.screen")
    Q_INTERFACES(luna::LunaPlugin)
public:
    QString name() const override;
    void initialize(luna::Luna * luna) override;
    void finalize(luna::Luna * luna) override;
};

#endif // SCREENPLUGIN_H
