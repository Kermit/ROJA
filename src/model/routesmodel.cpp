#include "routesmodel.h"

RoutesModel::RoutesModel(QObject *parent) :
    QAbstractListModel(parent)
{
    QHash<int, QByteArray> roles;
    roles[RouteDetailsIdRole] = "routedetailsID";
    roles[RouteRole] = "route";
    roles[RouteIDSRole] = "routeIDs";
    setRoleNames(roles);
}

void RoutesModel::addRoute(const RoutesItem item)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    items << item;
    endInsertRows();
}

int RoutesModel::rowCount(const QModelIndex &parent) const
{
    return items.count();
}

QVariant RoutesModel::data(const QModelIndex &index, int role) const
{
    if (index.row() < 0 || index.row() > items.count())
    {
        return QVariant();
    }

    const RoutesItem &item = items[index.row()];
    if (role == RouteDetailsIdRole)
    {
        return item.getRouteDetails();
    }
    else if (role == RouteRole)
    {
        return item.getRoute();
    }
    else if (role == RouteIDSRole)
    {
        return item.getRouteIDs();
    }

    return QVariant();
}

void RoutesModel::clearData()
{
    beginRemoveRows(QModelIndex(), 0, rowCount());
    items.clear();
    endRemoveRows();
}
