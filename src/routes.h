#ifndef ROUTES_H
#define ROUTES_H

#include <QtCore/QObject>
#include <QtCore/QMap>
#include <QtSql/QSqlQuery>

#include "src/page.h"
#include "src/routeoptions.h"

#include "qmlapplicationviewer.h"

#include <QElapsedTimer>

class QDeclarativeItem;
class StopsModel;
class RoutesModel;
class Timetable;

class Routes : public Page
{
    Q_OBJECT

private:
    //Main section
    QmlApplicationViewer *viewer;
    QDeclarativeItem *routesLoader;
    QDeclarativeItem *routesBox;
    QDeclarativeItem *routesTitleBar;
    QDeclarativeItem *routesBackButton;
    QDeclarativeItem *communicateText;

    // Search section
    QDeclarativeItem *searchBox;
    QDeclarativeItem *startStop;
    QDeclarativeItem *endStop;
    QDeclarativeItem *swapButton;
    QDeclarativeItem *przesiadkaButton;
    QDeclarativeItem *routesSearchButton;

    // Results section
    QDeclarativeItem *searchResultsBox;
    QDeclarativeItem *routeListView;
    QDeclarativeItem *searchDetailResultsBox;
    QDeclarativeItem *routeDetailsListView;
    QDeclarativeItem *routesTimetable;

    // Choose stop section
    QDeclarativeItem *chooseStopBox;
    QDeclarativeItem *chooseStopSearchButton;
    QDeclarativeItem *chooseStopSearch;
    QDeclarativeItem *chooseStopList;

    // Data sesction
    StopsModel *stopsModel;
    RoutesModel *routesModel;
    RoutesModel *routesDetailsModel;
    Timetable *timetable;
    QSqlQuery *frCheckNextStop;
    QSqlQuery *frGetAllOptions;
    QSqlQuery *srCheckRoute;

    bool startStopStatus;
    QString startStopName;
    int startStopID;
    QString endStopName;
    int endStopID;
    QMap<int, QString> routeList;

    QElapsedTimer tZapytanie;
    QElapsedTimer tSzukanieStraight;

    void init();
    void getStopsList(QString filter);    
    bool findStraightRoute(int startID, int stopID, int checkLineID, int checkRouteID, QString line);
    void findRoute(int przesiadki, RouteOptions &opt, QString line);
    void startSearching();
    void generateResult();
    void getDetailRouteData(QString line, QString text);

    void prepareFindRouteQueries();
    void destroyFindRouteQueries();
    void prepareStraightRouteQuery();
    void destroyStraightRouteQuery();

public:
    explicit Routes(QObject *parent = 0, QmlApplicationViewer *applicationViewer = 0);
    virtual ~Routes() {}
    void show();
    void hide();

private slots:
    void chooseStopClicked(bool startStop);
//    void swapButtonClicked();
    void searchButtonClicked();
    void routesBackButtonClicked(QString page);
    void chooseSearchButtonClicked();
    void filter(QString text);
    void chooseStopRowClicked(QString stopName, int stopID);
    void routeRowClicked(int routeDetailsID, QString routeIDs, QString route);
    void routeDetailRowClicked(int routeDetailsID, QString routeIDs, QString route);

    void startSearchNow();
    void hideCommunicateText();
};

#endif // ROUTES_H
