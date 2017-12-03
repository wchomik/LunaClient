#ifndef LEGACYUDPPLUGIN_H
#define LEGACYUDPPLUGIN_H

#include <lunaplugin.h>

class LegacyUdpPlugin : public luna::LunaPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.luna.udplegacy")
    Q_INTERFACES(luna::LunaPlugin)
public:
    void initialize(luna::Luna * luna) override;
    void finalize(luna::Luna * luna) override;
};

#endif // LEGACYUDPPLUGIN_H
