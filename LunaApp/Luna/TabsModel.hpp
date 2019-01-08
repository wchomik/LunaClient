#pragma once

#include <QObject>
#include <QQuickItem>

class TabsModel : public QObject
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
