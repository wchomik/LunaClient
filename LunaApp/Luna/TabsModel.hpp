#pragma once

#include <QAbstractListModel>
#include <QQuickItem>

#include <memory>

class TabsModel : public QAbstractListModel
{
public:
    int rowCount(QModelIndex const & parent = QModelIndex()) const override;
    QVariant data(QModelIndex const & index, int role) const override;
    QHash<int, QByteArray> roleNames() const override;

    void add(QString name, std::unique_ptr<QQuickItem> && qml);
private:
    struct Entry
    {
        QString name;
        std::unique_ptr<QQuickItem> qml;
    };
    std::vector<Entry> mEntries;
};
