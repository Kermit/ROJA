#include "stopsmodel.h"

StopsModel::StopsModel(QObject *parent) :
    QAbstractListModel(parent)
{
    QHash<int, QByteArray> roles;
    roles[stopIdRole] = "stopID";
    roles[stopNameRole] = "stopName";
    roles[stopCommuneRole] = "stopCommune";
    setRoleNames(roles);
}

void StopsModel::addStop(const StopsItem item)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    items << item;
    endInsertRows();
}

int StopsModel::rowCount(const QModelIndex &parent) const
{
    return items.count();
}

QVariant StopsModel::data(const QModelIndex &index, int role) const
{
    if (index.row() < 0 || index.row() > items.count())
    {
            return QVariant();
    }

    const StopsItem &item = items[index.row()];
    if (role == stopIdRole)
    {
            return item.getID();
    }
    else if (role == stopNameRole)
    {
            return item.getName();
    }
    else if (role == stopCommuneRole)
    {
            return item.getCommune();
    }

    return QVariant();
}

void StopsModel::clearData()
{
    beginRemoveRows(QModelIndex(), 0, rowCount());
    items.clear();
    endRemoveRows();
}
