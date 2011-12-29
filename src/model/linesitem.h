#ifndef LINESITEM_H
#define LINESITEM_H

#include <QtCore/QString>

class LinesItem
{
private:
    int id;
    QString number;
    int routeID;
    QString wayName;

public:
    explicit LinesItem(const int id, const QString &number, const int routeID, const QString &wayName);
    LinesItem() {}
    int getID() const;
    QString getNumber() const;
    int getRouteID() const;
    QString getWayName() const;
};

#endif // LINESITEM_H
