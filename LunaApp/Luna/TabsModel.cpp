#include "TabsModel.hpp"

enum
{
    nameRole = Qt::UserRole,
    qmlRole,
};

int TabsModel::rowCount(QModelIndex const & parent) const
{
    return static_cast<int>(mEntries.size());
}

QVariant TabsModel::data(QModelIndex const & index, int const role) const
{
    if (!index.isValid() || static_cast<size_t>(index.row()) >= mEntries.size()) {
        return {};
    }

    auto const & entry = mEntries[index.row()];

    switch (role) {
    case nameRole:
        return entry.name;
    case qmlRole:
        return QVariant::fromValue<QQuickItem *>(entry.qml.get());
    default:
        return {};
    }
}

QHash<int, QByteArray> TabsModel::roleNames() const
{
    return {
        {nameRole, "name"},
        {qmlRole, "qml"},
    };
}

void TabsModel::add(QString name, std::unique_ptr<QQuickItem> && qml)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    mEntries.push_back({name, std::move(qml)});
    endInsertRows();
}
