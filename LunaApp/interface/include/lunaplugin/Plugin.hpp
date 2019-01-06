#pragma once

#include "lunaplugin_global.h"

#include <QObject>

namespace lunacore {
    class Luna;

    class LUNAPLUGINSHARED_EXPORT LunaPlugin : public QObject {
    public:
        explicit LunaPlugin() = default;
        virtual ~LunaPlugin() = default;

        virtual QString name() const = 0;
        virtual void initialize(Luna * lunacore) = 0;
        virtual void finalize(Luna * lunacore) = 0;
    };
}

Q_DECLARE_INTERFACE(lunacore::LunaPlugin, "org.luna.plugin")
