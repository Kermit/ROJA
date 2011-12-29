#include "linesstopsitem.h"

LinesStopsItem::LinesStopsItem(const int lineID, const int routeID, const int stopID, const QString stopName,
                               const QString stopCommune, const bool stopOnDemand, const bool stopObligatory,
                               const int routesDetailsID) :
    lineID(lineID), routeID(routeID), stopID(stopID), stopName(stopName), stopCommune(stopCommune),
    stopOnDemand(stopOnDemand), stopObligatory(stopObligatory), routesDetailsID(routesDetailsID) {}
