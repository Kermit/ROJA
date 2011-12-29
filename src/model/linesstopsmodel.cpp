#include "linesstopsmodel.h"

LinesStopsModel::LinesStopsModel(QObject *parent) :
    QAbstractListModel(parent)
{
    QHash<int, QByteArray> roles;
    roles[LineIdRole] = "lineID";
    roles[RouteIDRole] = "routeID";
    roles[StopIDRole] = "stopID";
    roles[StopNameRole] = "stopName";
    roles[StopCommuneRole] = "stopCommune";
    roles[StopOnDemandRole] = "stopOnDemand";
    roles[StopObligatoryRole] = "stopObligatory";
    roles[RoutesDetailsIDRole] = "routesDetailsID";
    setRoleNames(roles);
}

void LinesStopsModel::addStop(const LinesStopsItem item)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    items << item;
    endInsertRows();
}

int LinesStopsModel::rowCount(const QModelIndex &parent) const
{
    return items.count();
}

QVariant LinesStopsModel::data(const QModelIndex &index, int role) const
{
    if (index.row() < 0 || index.row() > items.count())
    {
        return QVariant();
    }

    const LinesStopsItem &item = items[index.row()];
    if (role == LineIdRole)
    {
        return item.getLineID();
    }
    else if (role == RouteIDRole)
    {
        return item.getRouteID();
    }
    else if (role == StopIDRole)
    {
        return item.getStopID();
    }
    else if (role == StopNameRole)
    {
        return item.getStopName();
    }
    else if (role == StopCommuneRole)
    {
        return item.getStopCommune();
    }
    else if (role == StopOnDemandRole)
    {
        return item.getStopOnDemand();
    }
    else if (role == StopObligatoryRole)
    {
        return item.getStopObligatory();
    }
    else if (role == RoutesDetailsIDRole)
    {
        return item.getRoutesDetailsID();
    }

    return QVariant();
}

void LinesStopsModel::clearData()
{
    beginRemoveRows(QModelIndex(), 0, rowCount());
    items.clear();
    endRemoveRows();
}
