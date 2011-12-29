#include "linesmodel.h"

LinesModel::LinesModel(QObject *parent) :
    QAbstractListModel(parent)
{
    QHash<int, QByteArray> roles;
    roles[IdRole] = "lineID";
    roles[NumberRole] = "lineNumber";
    roles[RouteIDRole] = "lineRouteID";
    roles[WayRole] = "lineWayName";
    setRoleNames(roles);
}

void LinesModel::addLine(const LinesItem item)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    items << item;
    endInsertRows();
}

int LinesModel::rowCount(const QModelIndex &parent) const
{
    return items.count();
}

QVariant LinesModel::data(const QModelIndex &index, int role) const
{
    if (index.row() < 0 || index.row() > items.count())
    {
            return QVariant();
    }

    const LinesItem &item = items[index.row()];
    if (role == IdRole)
    {
            return item.getID();
    }
    else if (role == NumberRole)
    {
            return item.getNumber();
    }
    else if (role == RouteIDRole)
    {
            return item.getRouteID();
    }
    else if (role == WayRole)
    {
            return item.getWayName();
    }

    return QVariant();
}

void LinesModel::sort()
{
    qSort(items.begin(), items.end(), compareNames);
}

bool LinesModel::compareNames(const LinesItem &s1, const LinesItem &s2)
{
    return s1.getNumber().compare(s2.getNumber()) > 0;
}

void LinesModel::clearData()
{
    beginRemoveRows(QModelIndex(), 0, rowCount());
    items.clear();
    endRemoveRows();
}
