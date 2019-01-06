#include "tabsmodel.h"

namespace lunacore {
    lunacore::TabsModel::TabsModel(QObject *parent)  :
        QObject(parent)
    {

    }

    void TabsModel::addTab(QQuickItem *item, QString &name) {
        mItems.append(item);
        mNames.append(name);
        namesChanged();
    }

    QQmlListProperty<QQuickItem> TabsModel::items() {
        return QQmlListProperty<QQuickItem>(this, mItems);
    }

    QStringList & TabsModel::names() {
        return mNames;
    }
}
