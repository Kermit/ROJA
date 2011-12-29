#ifndef STOPSITEM_H
#define STOPSITEM_H

#include <QtCore/QString>

class StopsItem
{
private:
    int id;
    QString name;
    QString commune;

public:
    StopsItem(const int id, const QString &name, const QString &commune);
    int getID() const;
    QString getName() const;
    QString getCommune() const;
};

#endif // STOPSITEM_H
