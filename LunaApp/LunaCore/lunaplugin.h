#ifndef LUNAPLUGIN_H
#define LUNAPLUGIN_H

#include <memory>

#include <QString>
#include <QtPlugin>
//#include <QQuickItem>

#include "lunacore_global.h"
#include "provider.h"

namespace luna {
    class LUNACORESHARED_EXPORT LunaPlugin {
    public:
        virtual ~LunaPlugin();

        virtual QString name() = 0;
        //virtual QQuickItem * createItem() = 0;
        virtual std::unique_ptr<Provider> createProvider() = 0;
    };
}

#define LunaPlugin_iid "org.luna.plugin"

Q_DECLARE_INTERFACE(luna::LunaPlugin, LunaPlugin_iid)

#endif // LUNAPLUGIN_H
