#include "linesitem.h"

LinesItem::LinesItem(const int id, const QString &number, const int routeID, const QString &wayName) :
    id(id), number(number), routeID(routeID), wayName(wayName) {}

int LinesItem::getID() const
{
    return id;
}

QString LinesItem::getNumber() const
{
    return number;
}

int LinesItem::getRouteID() const
{
    return routeID;
}

QString LinesItem::getWayName() const
{
    return wayName;
}
