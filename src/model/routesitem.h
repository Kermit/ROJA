#ifndef ROUTESITEM_H
#define ROUTESITEM_H

#include <QtCore/QString>

class RoutesItem
{
private:
    int routeDetails;
    QString route;
    QString routeIDs;

public:
    RoutesItem(int routeDetails, QString route, QString routeIDs);
    int getRouteDetails() const { return routeDetails; }
    QString getRoute() const { return route; }
    QString getRouteIDs() const { return routeIDs; }
};

#endif // ROUTESITEM_H
