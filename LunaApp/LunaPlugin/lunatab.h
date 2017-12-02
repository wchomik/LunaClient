#ifndef LUNATAB_H
#define LUNATAB_H

#include <QString>
#include <QUrl>
#include <QObject>

#include <manager.h>

#include "lunaplugin_global.h"

namespace luna {
    class LUNAPLUGINSHARED_EXPORT Tab
    {
    public:
        virtual ~Tab();
        virtual void activate(Manager * manager) = 0;
        virtual void deactivate(Manager * manager) = 0;
        virtual QString displayName() const = 0;
        virtual int displayOrder() const = 0;
        virtual QUrl itemUrl() const = 0;
        virtual QObject * model() = 0;
    };
}

#endif // LUNATAB_H
