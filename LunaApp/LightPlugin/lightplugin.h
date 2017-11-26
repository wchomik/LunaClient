#ifndef LIGHTPLUGIN_H
#define LIGHTPLUGIN_H

#include <QObject>
#include <lunaplugin.h>

#include "lightmodel.h"

namespace luna {
    class LightPlugin : public QObject, public luna::LunaPlugin
    {
        Q_OBJECT
        Q_PLUGIN_METADATA(IID LunaPlugin_iid)
        Q_INTERFACES(luna::LunaPlugin)
    public:
        LightPlugin();
        ~LightPlugin();

        QString name() override;
        std::shared_ptr<luna::Provider> createProvider() override;
        QObject * model() override;
    protected:
        QUrl itemUrl() override;

    private:
        std::unique_ptr<LightModel> mModel;
    };
}

#endif // LIGHTPLUGIN_H
