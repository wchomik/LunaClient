#ifndef CONFIGURABLEPLUGIN_H
#define CONFIGURABLEPLUGIN_H

#include <QString>
#include <QUrl>
#include <QObject>

#include <lunacore/manager.h>

#include "lunaplugin_global.h"

namespace luna {
    class LUNAPLUGINSHARED_EXPORT ConfigurablePlugin
    {
    public:
        virtual ~ConfigurablePlugin();
        virtual QString displayName() const = 0;
        virtual int displayOrder() const = 0;
        virtual QUrl itemUrl() const = 0;
        virtual QObject * model() = 0;
    };
}
#endif // CONFIGURABLEPLUGIN_H
