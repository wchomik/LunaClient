#ifndef TABSMODEL_H
#define TABSMODEL_H

#include <QObject>
#include <QQuickItem>

#include "lunaplugin_global.h"

namespace lunacore {
    class LUNAPLUGINSHARED_EXPORT TabsModel : public QObject
    {
        Q_OBJECT
        Q_PROPERTY(QQmlListProperty<QQuickItem> items READ items NOTIFY itemsChanged)
        Q_PROPERTY(QStringList names READ names NOTIFY namesChanged)
    public:
        TabsModel(QObject * parent = nullptr);
        void addTab(QQuickItem * item, QString & name);

        QQmlListProperty<QQuickItem> items();
        QStringList & names();
    signals:
        void tabSelected(int index);

        void itemsChanged();
        void namesChanged();
    private:
        QList<QQuickItem *> mItems;
        QStringList mNames;
    };
}

#endif // TABSMODEL_H
