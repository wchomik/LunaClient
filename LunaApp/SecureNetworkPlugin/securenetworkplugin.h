#ifndef SECURENETWORKPLUGIN_H
#define SECURENETWORKPLUGIN_H

#include <lunaplugin/lunaplugin.h>

class SecureNetworkPlugin : public luna::LunaPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.luna.securenetwork")
    Q_INTERFACES(luna::LunaPlugin)
public:
    QString name() const override;
    void initialize(luna::Luna * luna) override;
    void finalize(luna::Luna * luna) override;
};

#endif // SECURENETWORKPLUGIN_H
