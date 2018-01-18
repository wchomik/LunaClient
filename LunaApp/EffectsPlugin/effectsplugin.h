#ifndef EFFECTSPLUGIN_H
#define EFFECTSPLUGIN_H

#include <lunaplugin/lunaplugin.h>

class EffectsPlugin : public luna::LunaPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.luna.effects")
    Q_INTERFACES(luna::LunaPlugin)
public:
    QString name() const override;
    void initialize(luna::Luna * luna) override;
    void finalize(luna::Luna * luna) override;
};

#endif // EFFECTSPLUGIN_H
