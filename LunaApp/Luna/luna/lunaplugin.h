#ifndef LUNAPLUGIN_H
#define LUNAPLUGIN_H

#include <QString>
#include <QQuickItem>
#include <memory>

#include "provider.h"

namespace luna {
    class LunaPlugin {
    public:
        virtual ~LunaPlugin();

        virtual QString name() = 0;
        virtual QQuickItem * createItem() = 0;
        virtual std::unique_ptr<Provider> createProvider() = 0;
    };
}

#endif // LUNAPLUGIN_H
