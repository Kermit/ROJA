#ifndef STOPSMODEL_H
#define STOPSMODEL_H

#include <QtCore/QAbstractListModel>
#include <QtCore/QList>

#include "src/model/stopsitem.h"

class StopsModel : public QAbstractListModel
{
    Q_OBJECT

private:
    QList<StopsItem> items;

public:    
    enum StopsRoles
    {
        stopIdRole = Qt::UserRole + 1,
        stopNameRole,
        stopCommuneRole
    };

    explicit StopsModel(QObject *parent = 0);
    void addStop(const StopsItem item);
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    void clearData();
};

#endif // STOPSMODEL_H
