#ifndef SCREENPLUGIN_H
#define SCREENPLUGIN_H

#include <QObject>

#include <luna/interface/lunaplugin.h>

class ScreenPlugin : public luna::interface::LunaPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.luna.screen")
    Q_INTERFACES(luna::interface::LunaPlugin)
public:
    QString name() const override;
    void initialize(luna::interface::Luna * lunacore) override;
    void finalize(luna::interface::Luna * lunacore) override;
};

#endif // SCREENPLUGIN_H
