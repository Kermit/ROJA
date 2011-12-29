#ifndef LINESSTOPSITEM_H
#define LINESSTOPSITEM_H

#include <QtCore/QString>

class LinesStopsItem
{
private:
    int lineID;
    int routeID;
    int stopID;
    QString stopName;
    QString stopCommune;
    bool stopOnDemand;
    bool stopObligatory;
    int routesDetailsID;

public:
    LinesStopsItem(const int lineID, const int routeID, const int stopID, const QString stopName,
                   const QString stopCommune, const bool stopOnDemand, const bool stopObligatory,
                   const int routesDetailsID);

    int getLineID() const { return lineID; }
    int getRouteID() const { return routeID; }
    int getStopID() const { return stopID; }
    QString getStopName() const { return stopName; }
    QString getStopCommune() const { return stopCommune; }
    bool getStopOnDemand() const { return stopOnDemand; }
    bool getStopObligatory() const { return stopObligatory; }
    int getRoutesDetailsID() const { return routesDetailsID; }

};

#endif // LINESSTOPSITEM_H
