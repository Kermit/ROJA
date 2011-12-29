#include "stopsitem.h"

StopsItem::StopsItem(const int id, const QString &name, const QString &commune) :
    id(id), name(name), commune(commune) {}

int StopsItem::getID() const
{
    return id;
}

QString StopsItem::getName() const
{
    return name;
}

QString StopsItem::getCommune() const
{
    return commune;
}
