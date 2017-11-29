#include "lunaplugin.h"

#include <QDebug>
#include <QQmlEngine>
#include <QQmlContext>

namespace luna {
    LunaPlugin::~LunaPlugin() {}

    QQuickItem * LunaPlugin::createItem(QQmlEngine * engine) {
        engine->rootContext()->setContextProperty(name(), model());

        const QUrl url = itemUrl();
        QQmlComponent component(engine, url);

        if (!component.isReady()) {
            qDebug() << component.errorString();
        } else {
            QObject * object = component.create();
            if (nullptr != object) {
                QQuickItem * quickItem = qobject_cast<QQuickItem *>(object);
                if (nullptr != quickItem) {
                    return quickItem;
                } else {
                    delete object;
                    qDebug() << "Instantiated pluigin is not a QQuickItem";
                }
            } else {
                qDebug() << "Could not instantiate plugin: " << name() << " URL: " << url;
            }
        }
        return nullptr;
    }
}

