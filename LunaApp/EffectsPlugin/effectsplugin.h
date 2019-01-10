#ifndef EFFECTSPLUGIN_H
#define EFFECTSPLUGIN_H

#include <luna/interface/lunaplugin.h>

class EffectsPlugin : public luna::interface::LunaPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.luna.effects")
    Q_INTERFACES(luna::interface::LunaPlugin)
public:
    QString name() const override;
    void initialize(luna::interface::Luna * lunacore) override;
    void finalize(luna::interface::Luna * lunacore) override;
};

#endif // EFFECTSPLUGIN_H
