#include "stops.h"

#include <QtDeclarative/QDeclarativeContext>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlRecord>

#include "src/rojadatabase.h"
#include "src/model/stopsmodel.h"
#include "src/model/linesmodel.h"
#include "src/timetable.h"

#include <QElapsedTimer>
#include <QDebug>

Stops::Stops(QObject *parent, QmlApplicationViewer *applicationViewer) :
    Page(parent)
{
    viewer = applicationViewer;

    stopsModel = new StopsModel(this);
    timetable = new Timetable(this);
    stopsLinesModel = new LinesModel(this);

    init();
}

Stops::~Stops() {}

void Stops::init()
{
    getData("");

    viewer->rootContext()->setContextProperty("stopsModel", stopsModel);
    viewer->rootContext()->setContextProperty("stopsTimetableModel", timetable->getModel());
    viewer->rootContext()->setContextProperty("stopsLinesModel",  stopsLinesModel);

    stopsLoader = viewer->rootObject()->findChild<QDeclarativeItem *>("stopsLoader");
    stopsLoader->setProperty("source", "assets:/qml/roja/Stops.qml");

    stopsSection = viewer->rootObject()->findChild<QDeclarativeItem *>("stopsSection");
    stopsTitleBar = viewer->rootObject()->findChild<QDeclarativeItem *>("stopsTitleBar");

    stopsListView = viewer->rootObject()->findChild<QDeclarativeItem *>("stopsListView");
    connect(stopsListView, SIGNAL(indexChanged(QString, int)), this, SLOT(stopClicked(QString, int)));

    stopsContent = viewer->rootObject()->findChild<QDeclarativeItem *>("stopsContent");
    stopsLinesContent = viewer->rootObject()->findChild<QDeclarativeItem *>("stopsLinesContent");
    stopsLinesLoader = viewer->rootObject()->findChild<QDeclarativeItem *>("stopsLinesLoader");

    backButton = viewer->rootObject()->findChild<QDeclarativeItem *>("stopsBackButton");
    connect(backButton, SIGNAL(backClicked(QString)), this, SLOT(backButtonClicked(QString)));
    searchLine = viewer->rootObject()->findChild<QDeclarativeItem *>("stopsSearch");
    connect(searchLine, SIGNAL(filter(QString)), this, SLOT(filter(QString)));
    searchButton = viewer->rootObject()->findChild<QDeclarativeItem *>("stopSearchButton");
    connect(searchButton, SIGNAL(searchButtonClicked()), this, SLOT(searchButtonClicked()));
}

void Stops::show()
{
    stopsLoader->setProperty("visible", true);
}

void Stops::hide()
{
    stopsLoader->setProperty("visible", false);
}

void Stops::getData(QString text)
{
    QString queryString;

    if (text.isEmpty())
    {
        queryString = "SELECT stops.id AS stopID, stops.name AS stopName, communes.name AS communeName FROM"
                " stops LEFT JOIN communes ON stops.communeID = communes.id ORDER BY stops.name";
    }
    else
    {
        queryString = "SELECT stops.id AS stopID, stops.name AS stopName, communes.name AS communeName FROM"
                " stops LEFT JOIN communes ON stops.communeID = communes.id WHERE stops.name LIKE '%" + text + "%'"
                " ORDER BY stops.name";
    }

    QSqlQuery query(queryString, RojaDatabase::getInstance()->getDatabase());
    qDebug() << query.lastQuery();
    int idColumn = query.record().indexOf("stopID");
    int stopNameColumn = query.record().indexOf("stopName");
    int communeNameColumn = query.record().indexOf("communeName");

    int id;
    QString stopName;
    QString communeName;

    while (query.next())
    {
        id = query.value(idColumn).toInt();
        stopName = query.value(stopNameColumn).toString();
        communeName = query.value(communeNameColumn).toString();

        stopsModel->addStop(StopsItem(id, stopName, communeName));
    }
}

void Stops::stopClicked(QString stopName, int stopID)
{
    searchLine->setProperty("state", "hide");
    currentStop = stopName;
    getStopsLinesData(stopID);
    stopsLinesLoader->setProperty("source", "assets:/qml/roja/StopsLines.qml");

    stopsSection->setProperty("page", "LinesList");
    backButton->setProperty("visible", true);

    stopsTitleBar->setProperty("text", currentStop);
    stopsTitleBar->setProperty("textPointSize", 6);

    stopsLinesListView = viewer->rootObject()->findChild<QDeclarativeItem *>("stopsLinesListView");
    connect(stopsLinesListView, SIGNAL(indexChanged(QString, QString, int)),
            this, SLOT(stopLineRowClicked(QString, QString, int)));

    stopLinesBox = viewer->rootObject()->findChild<QDeclarativeItem *>("stopLinesBox");
    slDetailsContent = viewer->rootObject()->findChild<QDeclarativeItem *>("slDetailsContent");
    slDetailsLoader = viewer->rootObject()->findChild<QDeclarativeItem *>("slDetailsLoader");

    searchButton->setProperty("visible", false);
    searchLine->setProperty("state", "hide");
    stopsContent->setProperty("visible", false);
    stopsLinesContent->setProperty("visible", true);
}

void Stops::getStopsLinesData(int stopID)
{
    QString queryString("SELECT lines.number AS lineNumber, routesdetails.id AS routedetailID,"
                        " stops.name AS stopName FROM ((routesdetails INNER JOIN lines ON routesdetails.lineID = lines.id)"
                        " INNER JOIN routes ON routesdetails.routeID = routes.id) INNER JOIN stops ON"
                        " routes.stopID = stops.id WHERE routesdetails.stopID = " + QString::number(stopID));

    QSqlQuery query(queryString, RojaDatabase::getInstance()->getDatabase());
    int routeDetailsIDColumn = query.record().indexOf("routedetailID");
    int numberColumn = query.record().indexOf("lineNumber");
    int stopNameColumn = query.record().indexOf("stopName");

    int routeDetailsID;
    QString number;
    QString stopName;

    while (query.next())
    {
        routeDetailsID = query.value(routeDetailsIDColumn).toInt();
        number = query.value(numberColumn).toString();
        stopName = query.value(stopNameColumn).toString();

        stopsLinesModel->addLine(LinesItem(0, number, routeDetailsID, stopName));
    }
}

void Stops::backButtonClicked(QString page)
{
    if (page == "LinesList")
    {
        stopsLinesModel->clearData();
        stopsLinesContent->setProperty("visible", false);
        stopsContent->setProperty("visible", true);

        disconnect(stopsLinesListView, 0, 0, 0);
        stopsLinesLoader->setProperty("source", "");
        backButton->setProperty("visible", false);
        stopsSection->setProperty("page", "Main");
        stopsTitleBar->setProperty("text", "Przystanki");
        stopsTitleBar->setProperty("textPointSize", 7);
        searchButton->setProperty("visible", true);
    }
    else if (page == "Timetable")
    {
        timetable->clearData();
        slDetailsContent->setProperty("visible", false);
        stopLinesBox->setProperty("visible", true);

        stopsSection->setProperty("page", "LinesList");
        stopsTitleBar->setProperty("text", " ");
    }
}

void Stops::searchButtonClicked()
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

void Stops::stopLineRowClicked(QString lineNumber, QString lineWayName, int routesDetailsID)
{
    QElapsedTimer time;
    time.start();
    timetable->getData(0, 0, 0, routesDetailsID);
    qDebug() << "Tworzenie rozkladu: " << time.elapsed();

    time.start();
    stopsSection->setProperty("page", "Timetable");
    backButton->setProperty("visible", true);

    stopsTitleBar->setProperty("text", currentStop + "<br>" + lineNumber + " - " + lineWayName);
    stopsTitleBar->setProperty("textPointSize", 6);

    stopLinesBox->setProperty("visible", false);
    slDetailsContent->setProperty("visible", true);
    qDebug() << "Ustawianie: " << time.elapsed();
}

void Stops::filter(QString text)
{
    stopsModel->clearData();
    text = text.toLower();
    getData(text);
}
