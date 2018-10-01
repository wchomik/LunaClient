#ifndef SECURENETWORKPLUGIN_H
#define SECURENETWORKPLUGIN_H

#include <lunaplugin/lunaplugin.h>

class SecureNetworkPlugin : public lunacore::LunaPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.luna.securenetwork")
    Q_INTERFACES(lunacore::LunaPlugin)
public:
    QString name() const override;
    void initialize(lunacore::Luna * lunacore) override;
    void finalize(lunacore::Luna * lunacore) override;
};

#endif // SECURENETWORKPLUGIN_H
