#ifndef LUNAPLUGIN_H
#define LUNAPLUGIN_H

#include <QtPlugin>

#include "lunaplugin_global.h"

namespace luna {
    class Luna;

    class LUNAPLUGINSHARED_EXPORT LunaPlugin : public QObject {
    public:
        explicit LunaPlugin(QObject * parent = nullptr);
        virtual ~LunaPlugin();

        virtual QString name() const = 0;
        virtual void initialize(Luna * luna) = 0;
        virtual void finalize(Luna * luna) = 0;

    };
}

Q_DECLARE_INTERFACE(luna::LunaPlugin, "org.luna.plugin")

#endif // LUNAPLUGIN_H
