#ifndef ROUTEOPTIONS_H
#define ROUTEOPTIONS_H

class RouteOptions
{
private:
    int id;
    int lineID;
    int routeID;
    int routeDetailsID;
    int startID;

public:
    RouteOptions() {}
    RouteOptions(int id, int lineID, int routeID, int routeDetailsID, int startID);
    int getID() { return id; }
    int getLineID() { return lineID; }
    int getRouteID() { return routeID; }
    int getRouteDetailsID() { return routeDetailsID; }
    int getStartID() { return startID; }
};

#endif // ROUTEOPTIONS_H
