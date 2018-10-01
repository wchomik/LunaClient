#ifndef EFFECTSPLUGIN_H
#define EFFECTSPLUGIN_H

#include <lunaplugin/lunaplugin.h>

class EffectsPlugin : public lunacore::LunaPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.luna.effects")
    Q_INTERFACES(lunacore::LunaPlugin)
public:
    QString name() const override;
    void initialize(lunacore::Luna * lunacore) override;
    void finalize(lunacore::Luna * lunacore) override;
};

#endif // EFFECTSPLUGIN_H
