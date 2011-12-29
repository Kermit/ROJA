#ifndef ROUTESMODEL_H
#define ROUTESMODEL_H

#include <QtCore/QAbstractListModel>
#include <QtCore/QList>

#include "src/model/routesitem.h"

class RoutesModel : public QAbstractListModel
{
    Q_OBJECT

private:
    QList<RoutesItem> items;

public:
    enum RoutesRoles
    {
        RouteDetailsIdRole = Qt::UserRole + 1,
        RouteRole,
        RouteIDSRole
    };

    explicit RoutesModel(QObject *parent = 0);
    void addRoute(const RoutesItem item);
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    void clearData();
};

#endif // ROUTESMODEL_H
