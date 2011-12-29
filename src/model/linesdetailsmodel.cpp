#include "linesdetailsmodel.h"

LinesDetailsModel::LinesDetailsModel(QObject *parent) :
    QAbstractListModel(parent)
{
    QHash<int, QByteArray> roles;
    roles[DayNameRole] = "dayName";
    roles[TimetableRole] = "timetable";
    roles[TimetableLegendRole] = "timetableLegend";
    setRoleNames(roles);
}

void LinesDetailsModel::addTimetable(const LinesDetailsItem item)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    items << item;
    endInsertRows();
}

int LinesDetailsModel::rowCount(const QModelIndex &parent) const
{
    return items.count();
}

QVariant LinesDetailsModel::data(const QModelIndex &index, int role) const
{
    if (index.row() < 0 || index.row() > items.count())
    {
        return QVariant();
    }

    const LinesDetailsItem &item = items[index.row()];
    if (role == DayNameRole)
    {
        return item.getDayName();
    }
    else if (role == TimetableRole)
    {
        return item.getTimetable();
    }
    else if (role == TimetableLegendRole)
    {
        return item.getTimetableLegend();
    }

    return QVariant();
}

void LinesDetailsModel::clearData()
{
    beginRemoveRows(QModelIndex(), 0, rowCount());
    items.clear();
    endRemoveRows();
}
