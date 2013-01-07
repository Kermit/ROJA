#include "lines.h"

#include <QtDeclarative/QDeclarativeContext>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlRecord>
#include <QtSql>

#include "src/rojadatabase.h"
#include "src/model/linesmodel.h"
#include "src/model/linesstopsmodel.h"
#include "src/model/linesdetailsmodel.h"
#include "src/timetable.h"

#include <QElapsedTimer>

#include <QDebug>

Lines::Lines(QObject *parent, QmlApplicationViewer *applicationViewer) :
    Page(parent)
{
    model = new LinesModel(this);
    timetable = new Timetable(this);
    stopsModel = new LinesStopsModel(this);

    getData("");

    viewer = applicationViewer;
    init();
}

void Lines::init()
{
    QDeclarativeContext *ss = viewer->rootContext();
    viewer->rootContext()->setContextProperty("linesModel",  model);
    viewer->rootContext()->setContextProperty("linesStopsModel",  stopsModel);
    viewer->rootContext()->setContextProperty("linesTimetableModel", timetable->getModel());

    linesLoader = viewer->rootObject()->findChild<QDeclarativeItem *>("linesLoader");
    linesLoader->setProperty("source", "assets:/qml/roja/Lines.qml");

    linesSection = viewer->rootObject()->findChild<QDeclarativeItem *>("linesSection");
    linesTitleBar = viewer->rootObject()->findChild<QDeclarativeItem *>("linesTitleBar");

    linesListView = viewer->rootObject()->findChild<QDeclarativeItem *>("linesListView");
    connect(linesListView, SIGNAL(indexChanged(int, int, QString, QString)), this, SLOT(lineRowClicked(int, int, QString, QString)));

    linesStopsLoader = viewer->rootObject()->findChild<QDeclarativeItem *>("linesStopsLoader");
    linesContent = viewer->rootObject()->findChild<QDeclarativeItem *>("linesContent");
    linesStopsBox = viewer->rootObject()->findChild<QDeclarativeItem *>("linesStopsBox");

    backButton = viewer->rootObject()->findChild<QDeclarativeItem *>("linesBackButton");
    connect(backButton, SIGNAL(backClicked(QString)), this, SLOT(backButtonClicked(QString)));
    searchLine = viewer->rootObject()->findChild<QDeclarativeItem *>("linesSearch");
    connect(searchLine, SIGNAL(filter(QString)), this, SLOT(filter(QString)));
    searchButton = viewer->rootObject()->findChild<QDeclarativeItem *>("searchButton");
    connect(searchButton, SIGNAL(searchButtonClicked()), this, SLOT(searchButtonClicked()));
}

Lines::~Lines() {}

void Lines::show()
{        
    linesLoader->setProperty("visible", true);
}

void Lines::hide()
{
    linesLoader->setProperty("visible", false);
}

void Lines::getData(QString filter)
{
    QString queryString;

    if (filter.isEmpty())
    {
        queryString = "SELECT lines.id AS lineId, lines.number AS lineNumber, routes.id AS routeID, stops.name AS stopName"
                " FROM (lines LEFT JOIN routes ON lines.id = routes.lineID)"
                " LEFT JOIN stops ON routes.stopID = stops.id ORDER BY lines.number ASC";
    }
    else
    {
        queryString  ="SELECT lines.id AS lineId, lines.number AS lineNumber, routes.id AS routeID, stops.name AS stopName"
                " FROM (lines LEFT JOIN routes ON lines.id = routes.lineID)"
                " LEFT JOIN stops ON routes.stopID = stops.id WHERE lineNumber LIKE '" + filter + "%'"
                " ORDER BY lines.number ASC";
    }

    QSqlQuery query(queryString, RojaDatabase::getInstance()->getDatabase());
    int idColumn = query.record().indexOf("lineId");
    int numberColumn = query.record().indexOf("lineNumber");
    int route1IDColumn = query.record().indexOf("routeID");
    int stopNameColumn = query.record().indexOf("stopName");

    int id;
    QString number;
    int route1ID;
    QString stopName;

    while (query.next())
    {
        id = query.value(idColumn).toInt();
        number = query.value(numberColumn).toString();
        route1ID = query.value(route1IDColumn).toInt();
        stopName = query.value(stopNameColumn).toString();

        model->addLine(LinesItem(id, number, route1ID, stopName));
    }
}

void Lines::lineRowClicked(int lineID, int routeID, QString lineNumber, QString lineWayName)
{    
    searchLine->setProperty("state", "hide");
    getStopsListData(lineID, routeID);

    linesStopsLoader->setProperty("source", "assets:/qml/roja/LinesStops.qml");

    linesSection->setProperty("page", "StopsList");
    backButton->setProperty("visible", true);   

    currentLineNumber = lineNumber;
    currentWayName = lineWayName;
    linesTitleBar->setProperty("text", currentLineNumber + " - " + currentWayName);
    linesTitleBar->setProperty("textPointSize", 6);

    linesStopsListView = viewer->rootObject()->findChild<QDeclarativeItem *>("linesStopsListView");
    connect(linesStopsListView, SIGNAL(indexChanged(int, int, int, QString, int)),
            this, SLOT(lineStopRowClicked(int,int,int,QString, int)));

    linesStopsContent = viewer->rootObject()->findChild<QDeclarativeItem *>("linesStopsContentS");
    linesDetailsContent = viewer->rootObject()->findChild<QDeclarativeItem *>("linesDetailsContent");
    linesDetailsLoader = viewer->rootObject()->findChild<QDeclarativeItem *>("linesDetailsLoader");

    searchButton->setProperty("visible", false);
    searchLine->setProperty("state", "hide");
    linesContent->setProperty("visible", false);
    linesStopsBox->setProperty("visible", true);
}

void Lines::getStopsListData(int lineID, int routeID)
{
    QString queryString("SELECT stops.id AS stopID, stops.name AS stopName, stops.communeID AS stopCommune,"
                        " routesdetails.onDemand AS stopOnDemand, routesdetails.obligatory AS stopObligatory,"
                        " routesdetails.id AS routeDetailsID "
                        " FROM routesdetails LEFT JOIN stops ON routesdetails.stopID = stops.id"
                        " WHERE routesdetails.lineID = " + QString::number(lineID) +
                        " AND routesdetails.routeID = " + QString::number(routeID) +
                        " AND routesdetails.stopID != -1"
                        " ORDER BY routeDetailsID");

    QSqlQuery query(queryString, RojaDatabase::getInstance()->getDatabase());
    int stopNameColumn = query.record().indexOf("stopName");
    int stopIDColumn = query.record().indexOf("stopID");
    int stopCommuneColumn = query.record().indexOf("stopCommune");
    int stopOnDemandColumn = query.record().indexOf("stopOnDemand");
    int stopObligatoryColumn = query.record().indexOf("stopObligatory");
    int routesDetialsIDColumn = query.record().indexOf("routeDetailsID");

    QString stopName;
    int stopID;
    QString stopCommune;
    bool stopOnDemand;
    bool stopObligatory;
    int routesDetailsID;

    while (query.next())
    {
        stopOnDemand = query.value(stopOnDemandColumn).toBool();
        stopObligatory = query.value(stopObligatoryColumn).toBool();
        stopName = query.value(stopNameColumn).toString();
        stopID = query.value(stopIDColumn).toInt();
        stopCommune = query.value(stopCommuneColumn).toString();
        routesDetailsID = query.value(routesDetialsIDColumn).toInt();

        if (stopOnDemand)
        {
            stopName += QString::fromUtf8(" n/ż");
        }

        if (stopObligatory)
        {
            stopName = "<i>" + stopName + "</i>";
        }

        stopsModel->addStop(LinesStopsItem(lineID, routeID, stopID, stopName, stopCommune, stopOnDemand,
                                           stopObligatory, routesDetailsID));
    }
}

void Lines::lineStopRowClicked(int lineID, int routeID, int stopID, QString stopName, int routesDetailsID)
{
    timetable->getData(stopID, lineID, routeID, routesDetailsID);

    linesSection->setProperty("page", "Timetable");
    backButton->setProperty("visible", true);

    linesTitleBar->setProperty("text", currentLineNumber + " - " + currentWayName + "<br>" + stopName);
    linesTitleBar->setProperty("textPointSize", 6);

    linesStopsContent->setProperty("visible", false);
    linesDetailsContent->setProperty("visible", true);
}

void Lines::backButtonClicked(QString page)
{
    if (page == "StopsList")
    {
        stopsModel->clearData();
        linesStopsBox->setProperty("visible", false);
        linesContent->setProperty("visible", true);

        disconnect(linesStopsListView, 0, 0, 0);
        linesStopsLoader->setProperty("source", "");
        backButton->setProperty("visible", false);
        linesSection->setProperty("page", "Main");
        linesTitleBar->setProperty("text", "Linie");
        linesTitleBar->setProperty("textPointSize", 7);
        searchButton->setProperty("visible", true);
    }
    else if (page == "Timetable")
    {
        timetable->clearData();
        linesDetailsContent->setProperty("visible", false);
        linesStopsContent->setProperty("visible", true);

        linesSection->setProperty("page", "StopsList");
        linesTitleBar->setProperty("text", currentLineNumber + " " + currentWayName);
    }
}

void Lines::searchButtonClicked()
{
    if (searchLine->property("state") == "show")
    {
        searchLine->setProperty("state", "hide");
    }
    else
    {
        viewer->setResizeMode(QmlApplicationViewer::SizeViewToRootObject);
        searchLine->setProperty("state", "show");
    }
}

void Lines::filter(QString text)
{
    model->clearData();
    getData(text);
}
