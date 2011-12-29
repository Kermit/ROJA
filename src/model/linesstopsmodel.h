#ifndef LINESSTOPSMODEL_H
#define LINESSTOPSMODEL_H

#include <QtCore/QAbstractListModel>
#include <QtCore/QList>

#include "src/model/linesstopsitem.h"

class LinesStopsModel : public QAbstractListModel
{
    Q_OBJECT
private:
    QList<LinesStopsItem> items;

public:
    enum LinesStopsRoles
    {
        LineIdRole = Qt::UserRole + 1,
        RouteIDRole,
        StopIDRole,
        StopNameRole,
        StopCommuneRole,
        StopOnDemandRole,
        StopObligatoryRole,
        RoutesDetailsIDRole
    };

    explicit LinesStopsModel(QObject *parent = 0);
    void addStop(const LinesStopsItem item);
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    void clearData();
};

#endif // LINESSTOPSMODEL_H
