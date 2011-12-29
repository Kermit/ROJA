#ifndef LINESDETAILSMODEL_H
#define LINESDETAILSMODEL_H

#include <QtCore/QAbstractListModel>
#include <QtCore/QList>

#include "src/model/linesdetailsitem.h"

class LinesDetailsModel : public QAbstractListModel
{
    Q_OBJECT

private:
    QList<LinesDetailsItem> items;

public:
    enum LinesDetailsRoles
    {
        DayNameRole = Qt::UserRole + 1,
        TimetableRole,
        TimetableLegendRole
    };

    explicit LinesDetailsModel(QObject *parent = 0);
    void addTimetable(const LinesDetailsItem item);
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    void clearData();
};

#endif // LINESDETAILSMODEL_H
