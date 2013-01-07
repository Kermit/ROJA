#include "routes.h"

#include <QtDeclarative/QDeclarativeItem>
#include <QtDeclarative/QDeclarativeContext>
#include <QtSql/QSqlRecord>

#include "src/model/stopsmodel.h"
#include "src/model/routesmodel.h"
#include "src/timetable.h"
#include "src/rojadatabase.h"
#include "src/common.h"

#include <QDebug>
#include <QElapsedTimer>
#include <QtSql>

Routes::Routes(QObject *parent, QmlApplicationViewer *applicationViewer) :
    Page(parent)
{
    viewer = applicationViewer;

    startStopID = -1;
    endStopID = -1;

    stopsModel = new StopsModel(this);
    routesModel = new RoutesModel(this);
    routesDetailsModel = new RoutesModel(this);
    timetable = new Timetable(this);

    init();
}

void Routes::init()
{
    viewer->rootContext()->setContextProperty("chooseStopModel", stopsModel);
    viewer->rootContext()->setContextProperty("routesModel", routesModel);
    viewer->rootContext()->setContextProperty("routesDetailModel", routesDetailsModel);
    viewer->rootContext()->setContextProperty("routesTimetableModel", timetable->getModel());

    routesLoader = viewer->rootObject()->findChild<QDeclarativeItem *>("routesLoader");
    routesLoader->setProperty("source", "assets:/qml/roja/Routes.qml");
    communicateText = viewer->rootObject()->findChild<QDeclarativeItem *>("communicateText");
    routesTitleBar = viewer->rootObject()->findChild<QDeclarativeItem *>("routesTitleBar");

    routesBox = viewer->rootObject()->findChild<QDeclarativeItem *>("routesBox");

    searchBox = viewer->rootObject()->findChild<QDeclarativeItem *>("searchBox");
    przesiadkaButton = viewer->rootObject()->findChild<QDeclarativeItem *>("przesiadkaButton");
    routesSearchButton = viewer->rootObject()->findChild<QDeclarativeItem *>("routesSearchButton");
    startStop = viewer->rootObject()->findChild<QDeclarativeItem *>("startStop");
    endStop = viewer->rootObject()->findChild<QDeclarativeItem *>("endStop");

    chooseStopBox = viewer->rootObject()->findChild<QDeclarativeItem *>("chooseStopBox");
    chooseStopSearchButton = viewer->rootObject()->findChild<QDeclarativeItem *>("chooseStopSearchButton");
    chooseStopSearch = viewer->rootObject()->findChild<QDeclarativeItem *>("chooseStopSearch");
    chooseStopList = viewer->rootObject()->findChild<QDeclarativeItem *>("chooseStopList");
    routesBackButton = viewer->rootObject()->findChild<QDeclarativeItem *>("routesBackButton");

    searchResultsBox = viewer->rootObject()->findChild<QDeclarativeItem *>("searchResultsBox");
    routeListView = viewer->rootObject()->findChild<QDeclarativeItem *>("routeListView");
    searchDetailResultsBox = viewer->rootObject()->findChild<QDeclarativeItem *>("searchDetailResultsBox");
    routeDetailsListView = viewer->rootObject()->findChild<QDeclarativeItem *>("routeDetailsListView");
    routesTimetable = viewer->rootObject()->findChild<QDeclarativeItem *>("routesTimetable");

    connect(routeListView, SIGNAL(indexChanged(int,QString,QString)), this, SLOT(routeRowClicked(int,QString,QString)));
    connect(routeDetailsListView, SIGNAL(indexChanged(int,QString,QString)), this, SLOT(routeDetailRowClicked(int,QString,QString)));
    connect(startStop, SIGNAL(clicked(bool)), this, SLOT(chooseStopClicked(bool)));
    connect(endStop, SIGNAL(clicked(bool)), this, SLOT(chooseStopClicked(bool)));
    connect(routesSearchButton, SIGNAL(clicked()), this, SLOT(searchButtonClicked()));
    connect(routesBackButton, SIGNAL(backClicked(QString)), this, SLOT(routesBackButtonClicked(QString)));
    connect(chooseStopSearchButton, SIGNAL(searchButtonClicked()), this, SLOT(chooseSearchButtonClicked()));
    connect(chooseStopSearch, SIGNAL(filter(QString)), this, SLOT(filter(QString)));
    connect(chooseStopList, SIGNAL(indexChanged(QString, int)), this, SLOT(chooseStopRowClicked(QString,int)));
}

void Routes::show()
{
    routesLoader->setProperty("visible", true);
}

void Routes::hide()
{
    routesLoader->setProperty("visible", false);
}

void Routes::hideCommunicateText()
{
    communicateText->setVisible(false);
    communicateText->setProperty("text", QString::fromUtf8("Szukam, proszę czekać ..."));
}

void Routes::chooseStopClicked(bool startStop)
{
    startStopStatus = startStop;
    getStopsList("");

    routesTitleBar->setProperty("text", "Wybierz przystanek");
    routesBox->setProperty("page", "ChooseStop");
    routesBackButton->setProperty("visible", true);
    chooseStopSearchButton->setProperty("visible", true);

    searchBox->setProperty("visible", false);
    chooseStopBox->setProperty("visible", true);
}

void Routes::getStopsList(QString filter)
{
    QString queryString;

    if (filter.isEmpty())
    {
        queryString = "SELECT stops.id AS stopID, stops.name AS stopName, communes.name AS communeName FROM"
                " stops LEFT JOIN communes ON stops.communeID = communes.id ORDER BY stops.name";
    }
    else
    {
        queryString = "SELECT stops.id AS stopID, stops.name AS stopName, communes.name AS communeName FROM"
                " stops LEFT JOIN communes ON stops.communeID = communes.id WHERE stops.name LIKE '%" + filter + "%'"
                " ORDER BY stops.name";
    }

    QSqlQuery query(queryString, RojaDatabase::getInstance()->getDatabase());
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

void Routes::routesBackButtonClicked(QString page)
{
    if (page == "ChooseStop")
    {
        routesTitleBar->setProperty("text", "Wyszukiwanie tras");
        routesBox->setProperty("page", "Main");
        routesBackButton->setProperty("visible", false);
        chooseStopSearchButton->setProperty("visible", false);
        chooseStopSearch->setProperty("inputFocus", false);

        chooseStopBox->setProperty("visible", false);
        searchBox->setProperty("visible", true);
    }

    if (page == "Route")
    {
        routesBox->setProperty("page", "Main");
        routesBackButton->setProperty("visible", false);

        routesTitleBar->setProperty("text", "Wyszukiwanie tras");
        searchResultsBox->setProperty("visible", false);
        searchBox->setProperty("visible", true);
        routesModel->clearData();
    }

    if (page == "DetailRoute")
    {
        routesBox->setProperty("page", "Route");

        routesTitleBar->setProperty("text", "Znalezione trasy");
        searchDetailResultsBox->setVisible(false);
        searchResultsBox->setVisible(true);
    }

    if (page == "TimetableA")
    {
        routesBox->setProperty("page", "Route");

        routesTitleBar->setProperty("text", "Znalezione trasy");
        routesTimetable->setVisible(false);
        searchResultsBox->setVisible(true);
    }

    if (page == "TimetableB")
    {
        routesBox->setProperty("page", "DetailRoute");

        routesTitleBar->setProperty("text", QString::fromUtf8("Szczegóły trasy"));
        routesTimetable->setVisible(false);
        searchDetailResultsBox->setVisible(true);
    }
}

void Routes::chooseSearchButtonClicked()
{
    if (chooseStopSearch->property("state") == "show")
    {
        chooseStopSearch->setProperty("state", "hide");
    }
    else
    {
        viewer->setResizeMode(QmlApplicationViewer::SizeViewToRootObject);
        chooseStopSearch->setProperty("state", "show");
    }
}

void Routes::filter(QString text)
{
    stopsModel->clearData();
    text = text.toLower();
    Common::convertSpecialChars(text);
    getStopsList(text);
}

void Routes::chooseStopRowClicked(QString stopName, int stopID)
{
    if (startStopStatus)
    {
        startStopName = stopName;
        startStopID = stopID;
        startStop->setProperty("text", stopName);
    }
    else
    {
        endStopName = stopName;
        endStopID = stopID;
        endStop->setProperty("text", stopName);
    }

    routesTitleBar->setProperty("text", "Wyszukiwanie tras");
    routesBox->setProperty("page", "Main");
    routesBackButton->setProperty("visible", false);
    chooseStopSearchButton->setProperty("visible", false);

    chooseStopBox->setProperty("visible", false);
    searchBox->setProperty("visible", true);
    chooseStopSearch->setProperty("inputFocus", false);
    stopsModel->clearData();
}

void Routes::searchButtonClicked()
{
    routeList.clear();

    if (endStopID == startStopID || endStopID == -1 || startStopID == -1)
    {
        communicateText->setProperty("text", QString::fromUtf8("Wybierz różne przystanki ..."));
        communicateText->setVisible(true);
        QTimer::singleShot(1000, this, SLOT(hideCommunicateText()));
    }
    else
    {
        communicateText->setVisible(true);
        QTimer::singleShot(10, this, SLOT(startSearchNow()));
    }
}

void Routes::startSearchNow()
{
    QElapsedTimer t1;
    t1.start();
    ok.clear();
    if (!przesiadkaButton->property("przesiadka").toBool())
    {
        prepareStraightRouteQuery();
        findStraightRoute(startStopID, endStopID, -1, -1, "");
        destroyStraightRouteQuery();
    }
    else
    {
        startSearching();
    }

    qDebug() << "Czas szukania to: " << t1.elapsed();
    communicateText->setVisible(false);
    generateResult();
    qDebug() << "Czas całkowity to: " << t1.elapsed();
}


void Routes::startSearching()
{
    QMap<int, RouteOptions> allOptions;
    prepareFindRouteQueries();

    QString linesQuery("SELECT id, lineID, routeID, routeDetailsID FROM routesdetails"
                       " WHERE stopID = " + QString::number(startStopID));

    QSqlQuery query(linesQuery, RojaDatabase::getInstance()->getDatabase());
    int idColumn = query.record().indexOf("id");
    int lineIDColumn = query.record().indexOf("lineID");
    int routeIDColumn = query.record().indexOf("routeID");
    int routeDetailsIDColumn = query.record().indexOf("routeDetailsID");

    int rID;
    int rLineID;
    int rRouteID;
    int rRouteDetailsID;

    while (query.next())
    {
        rID = query.record().value(idColumn).toInt();
        rLineID = query.record().value(lineIDColumn).toInt();
        rRouteID = query.record().value(routeIDColumn).toInt();
        rRouteDetailsID = query.record().value(routeDetailsIDColumn).toInt();

        RouteOptions opt = RouteOptions(rID, rLineID, rRouteID, rRouteDetailsID, startStopID);
        allOptions.insert(rRouteDetailsID, opt);
    }

    foreach (int key, allOptions.keys())
    {
        RouteOptions opt = allOptions.value(key);
        bool straightRoute = findStraightRoute(startStopID, endStopID, opt.getLineID(), opt.getRouteID(), "");

        if (straightRoute)
        {
            allOptions.remove(key);
            continue;
        }
        else
        {
            QString line = QString::number(opt.getLineID()) + "->";
            findRoute(1, opt, line);
        }
    }

    destroyFindRouteQueries();
}


void Routes::prepareFindRouteQueries()
{
    frGetNextStopID = new QSqlQuery(RojaDatabase::getInstance()->getDatabase());
    frGetNextStopID->setForwardOnly(true);
    frGetNextStopID->prepare("SELECT stopID FROM routesdetails WHERE id = :id");

    frCheckNextStop = new QSqlQuery(RojaDatabase::getInstance()->getDatabase());
    frCheckNextStop->setForwardOnly(true);
    frCheckNextStop->prepare("SELECT id FROM routesdetails WHERE routeID = :routeID AND stopID ="
                             " (SELECT stopID FROM routesdetails WHERE id = :id)");

    frGetAllOptions = new QSqlQuery(RojaDatabase::getInstance()->getDatabase());
    frGetAllOptions->setForwardOnly(true);
    frGetAllOptions->prepare("SELECT id, lineID, routeID, routeDetailsID, stopID FROM routesdetails"
                             " WHERE stopID = :stopID");

    prepareStraightRouteQuery();
}

void Routes::destroyFindRouteQueries()
{
    delete frGetNextStopID;
    frGetNextStopID = 0;

    delete frCheckNextStop;
    frCheckNextStop = 0;

    delete frGetAllOptions;
    frGetAllOptions = 0;

    destroyStraightRouteQuery();
}

void Routes::prepareStraightRouteQuery()
{
    csrCheckRoute = new QSqlQuery(RojaDatabase::getInstance()->getDatabase());
    csrCheckRoute->setForwardOnly(true);
    csrCheckRoute->prepare("SELECT routesdetails.id AS routedetailID,"
                           " stops.name AS stopName"
                           " FROM ((routesdetails INNER JOIN lines ON routesdetails.lineID = lines.id)"
                           " INNER JOIN routes ON routesdetails.routeID = routes.id) INNER JOIN stops ON"
                           " routes.stopID = stops.id WHERE routesdetails.stopID = :stopID AND routesdetails.lineID = :lineID AND"
                           " routesdetails.routeID = :routeID");

    csrGetAllLines = new QSqlQuery(RojaDatabase::getInstance()->getDatabase());
    csrGetAllLines->setForwardOnly(true);
    csrGetAllLines->prepare("SELECT id FROM routesdetails WHERE stopID = :startID"
                            " AND lineID = :lineID AND routeID = :routeID"
                            " AND id < :id");
}

void Routes::destroyStraightRouteQuery()
{
    delete csrCheckRoute;
    csrCheckRoute = 0;
}

bool Routes::findStraightRoute(int startID, int stopID, int checkLineID, int checkRouteID, QString line)
{
    bool result = false;
    QString linesQuery;

    if (checkLineID == -1 && checkRouteID == -1)
    {
        linesQuery = "SELECT id, lineID, routeID FROM routesdetails WHERE stopID = " + QString::number(startID);
    }
    else
    {
        linesQuery = "SELECT id, lineID, routeID FROM routesdetails WHERE stopID = " + QString::number(startID) +
                " AND lineID = " + QString::number(checkLineID) + " AND routeID = " + QString::number(checkRouteID);
    }

    QSqlQuery query(linesQuery, RojaDatabase::getInstance()->getDatabase());
    int idColumn = query.record().indexOf("id");
    int lineIDColumn = query.record().indexOf("lineID");
    int routeIDColumn = query.record().indexOf("routeID");

    int id;
    int lineID;
    int routeID;
    int secondID;

    while (query.next())
    {
        id = query.value(idColumn).toInt();
        lineID = query.value(lineIDColumn).toInt();
        routeID = query.value(routeIDColumn).toInt();

        csrCheckRoute->bindValue(":stopID", stopID);
        csrCheckRoute->bindValue(":lineID", lineID);
        csrCheckRoute->bindValue(":routeID", routeID);
        csrCheckRoute->exec();

        if (csrCheckRoute->next())
        {
            secondID = csrCheckRoute->record().value("routedetailID").toInt();
            if (secondID < id)
                continue;

            result = true;
            QString resultString = QString(QString::number(lineID) + "->" + QString::number(routeID));
            okMap.insert(routeID, resultString);
            routeList.insert(routeList.count(), line + resultString);
        }
    }

    return result;
}

bool Routes::checkStraightRoute(RouteOptions &routeOptions, QString line)
{
    bool result = false;
    csrCheckRoute->bindValue(":stopID", endStopID);
    csrCheckRoute->bindValue(":lineID", routeOptions.getLineID());
    csrCheckRoute->bindValue(":routeID", routeOptions.getRouteID());
    csrCheckRoute->exec();

    if (csrCheckRoute->next() && csrCheckRoute->record().value("routedetailID").toInt() > routeOptions.getID())
    {
        result = true;
        QString resultString = QString(QString::number(routeOptions.getLineID()) + "->" + QString::number(routeOptions.getRouteID()));
        okMap.insert(routeOptions.getRouteID(), resultString);
        routeList.insert(routeList.count(), line + resultString);
    }

    return result;
}

void Routes::findRoute(int przesiadki, RouteOptions &opt, QString line)
{
    QElapsedTimer t2;
    t2.start();
    QMap<int, RouteOptions> allOptions;
    int nextStopID = -1;

    if (opt.getRouteDetailsID() == -1)
    {
        return;
    }

    frGetNextStopID->bindValue(":id", opt.getRouteDetailsID());
    frGetNextStopID->exec();
    frGetNextStopID->next();
    nextStopID = frGetNextStopID->record().value("stopID").toInt();

    QElapsedTimer t3;
    t3.start();
    frGetAllOptions->bindValue(":stopID", nextStopID);
    frGetAllOptions->exec();

    int idColumn = frGetAllOptions->record().indexOf("id");
    int lineIDColumn = frGetAllOptions->record().indexOf("lineID");
    int routeIDColumn = frGetAllOptions->record().indexOf("routeID");
    int routeDetailsIDColumn = frGetAllOptions->record().indexOf("routeDetailsID");
    int stopIDColumn = frGetAllOptions->record().indexOf("stopID");

    int rID;
    int rLineID;
    int rRouteID;
    int rRouteDetailsID;
    int rStopID;

    while (frGetAllOptions->next())
    {
        rID = frGetAllOptions->record().value(idColumn).toInt();
        rLineID = frGetAllOptions->record().value(lineIDColumn).toInt();
        rRouteID = frGetAllOptions->record().value(routeIDColumn).toInt();
        rRouteDetailsID = frGetAllOptions->record().value(routeDetailsIDColumn).toInt();
        rStopID = frGetAllOptions->record().value(stopIDColumn).toInt();

        foreach (int key, allOptions.keys())
        {
            RouteOptions object = allOptions.value(key);
            if (object.getLineID() == rLineID && object.getRouteID() == rRouteID && object.getID() < rID)
            {
                allOptions.remove(key);
                continue;
            }
        }

        RouteOptions bOpt = RouteOptions(rID, rLineID, rRouteID, rRouteDetailsID, rStopID);
        allOptions.insert(rRouteDetailsID, bOpt);
    }
    qDebug() << "Czas pobrania wszystkich opcji: " << t3.elapsed();

    foreach (int key, allOptions.keys())
    {
        RouteOptions tempOpt = allOptions.value(key);

        QElapsedTimer t4;
        t4.start();
        if (tempOpt.getLineID() != opt.getLineID())
        {
            if (tempOpt.getRouteDetailsID() == -1)
            {
                return;
            }

            frCheckNextStop->bindValue(":id", tempOpt.getRouteDetailsID());
            frCheckNextStop->bindValue(":routeID", opt.getRouteID());
            frCheckNextStop->exec();
            if (frCheckNextStop->next())
            {
                allOptions.remove(key);
                qDebug() << "Czas sprawdzenia czy autobusy jadą w tą samą stronę 1: " << t4.elapsed();
                continue;
            }

            qDebug() << "Czas sprawdzenia czy autobusy jadą w tą samą stronę 2: " << t4.elapsed();
        }

        QElapsedTimer t5;
        t5.start();
        if (opt.getLineID() != tempOpt.getLineID() ||
                ((opt.getLineID() == tempOpt.getLineID()) && (opt.getRouteID() != tempOpt.getRouteID())))
        {
            if (opt.getLineID() == tempOpt.getLineID())
            {
//                allOptions.remove(key);
                continue;
            }

            if (przesiadki - 1 == 0)
            {
                QString mLine(line);
                mLine.append(QString::number(opt.getRouteID()));
                mLine.append("; ");
                mLine.append(QString::number(tempOpt.getStartID()));
                mLine.append("; ");

                checkStraightRoute(tempOpt, mLine);

                allOptions.remove(key);
                qDebug() << "Czas sprawdzenia bezpośredniego: " << t5.elapsed();
                continue;
            }
            else
            {
                QString mLine(line);
                mLine.append(";");
                mLine.append(QString(QString::number(tempOpt.getLineID()) + "->" + QString::number(tempOpt.getStartID())));
                findRoute(przesiadki -1, tempOpt, mLine);
            }
        }
        else
        {
            QString mLine(line);
            findRoute(przesiadki, tempOpt, mLine);
        }
    }

    qDebug() << "Czas \"Find route\" :" << t2.elapsed();
}

void Routes::generateResult()
{
    QString getRouteString("SELECT lines.number AS lineNumber, stops.name AS stopName"
                           " FROM (routes INNER JOIN stops ON routes.stopID = stops.id) INNER JOIN"
                           " lines ON routes.lineID = lines.id WHERE routes.id = :routeID AND routes.lineID = :lineID");
    QSqlQuery getRouteQuery(RojaDatabase::getInstance()->getDatabase());
    getRouteQuery.prepare(getRouteString);

    QString getStopString("SELECT name FROM stops WHERE id = :id");
    QSqlQuery getStopQuery(RojaDatabase::getInstance()->getDatabase());
    getStopQuery.prepare(getStopString);

    QString getRDID("SELECT id FROM routesdetails WHERE lineID = :lineID AND routeID = :routeID AND stopID = :stopID");
    QSqlQuery getRDIDQuery(RojaDatabase::getInstance()->getDatabase());
    getRDIDQuery.prepare(getRDID);

    foreach (int key, routeList.keys())
    {
        int routedetailsID = -1;
        QString newLine = "";
        QString line(routeList.value(key));
        QStringList mainParts(line.split(";"));

        foreach (QString str, mainParts)
        {
            if (str.contains("->"))
            {
                getRouteQuery.bindValue(":lineID", str.split("->")[0]);
                getRouteQuery.bindValue(":routeID", str.split("->")[1]);
                getRouteQuery.exec();
                getRouteQuery.next();
                newLine += getRouteQuery.record().value("lineNumber").toString();
                newLine += "->";
                newLine += getRouteQuery.record().value("stopName").toString();
            }
            else
            {
                str = str.replace(" ", "");
                getStopQuery.bindValue(":id", str);
                getStopQuery.exec();
                getStopQuery.next();
                newLine += "<br>";
                newLine += "Przesiadka: ";
                newLine += getStopQuery.record().value("name").toString();
                newLine += "<br>";
            }
        }

        if (mainParts.count() == 1)
        {
            getRDIDQuery.bindValue(":lineID", line.split("->")[0]);
            getRDIDQuery.bindValue(":routeID", line.split("->")[1]);
            getRDIDQuery.bindValue(":stopID", startStopID);
            getRDIDQuery.exec();
            getRDIDQuery.next();
            routedetailsID = getRDIDQuery.record().value("id").toInt();
        }

        routesModel->addRoute(RoutesItem(routedetailsID, newLine, line));
    }

    routesTitleBar->setProperty("text", "Znalezione trasy");
    routesBox->setProperty("page", "Route");
    routesBackButton->setProperty("visible", true);
    searchBox->setProperty("visible", false);
    searchResultsBox->setProperty("visible", true);
}

void Routes::routeRowClicked(int routeDetailsID, QString routeIDs, QString route)
{
    if (routeDetailsID != -1)
    {
        timetable->clearData();
        timetable->getData(0, 0, 0, routeDetailsID);

        if(routesBox->property("page") == "Route")
        {
            routesBox->setProperty("page", "TimetableA");
        }
        else
        {
            routesBox->setProperty("page", "TimetableB");
        }
        routesTitleBar->setProperty("text", QString::fromUtf8("Rozkład"));
        searchResultsBox->setVisible(false);
        routesTimetable->setVisible(true);
    }
    else
    {
        getDetailRouteData(routeIDs, route);

        routesBox->setProperty("page", "DetailRoute");
        routesTitleBar->setProperty("text", QString::fromUtf8("Szczegóły trasy"));
        searchResultsBox->setVisible(false);
        searchDetailResultsBox->setVisible(true);
    }
}

void Routes::getDetailRouteData(QString line, QString text)
{
    routesDetailsModel->clearData();

    QString getRDID("SELECT id FROM routesdetails WHERE lineID = :lineID AND routeID = :routeID AND stopID = :stopID");
    QSqlQuery getRDIDQuery(RojaDatabase::getInstance()->getDatabase());
    getRDIDQuery.prepare(getRDID);

    QStringList splittedLine = line.split(";");
    QStringList splittedText = text.split("<br>");
    int stopID;
    int lineID;
    int routeID;

    for (int i = 0; i < splittedLine.count(); ++i)
    {
        QString currentLine = splittedLine.value(i);
        if (i == 0)
        {
            stopID = startStopID;
            lineID = currentLine.split("->").value(0).toInt();
            routeID = currentLine.split("->").value(1).toInt();

            getRDIDQuery.bindValue(":lineID", lineID);
            getRDIDQuery.bindValue(":routeID", routeID);
            getRDIDQuery.bindValue(":stopID", stopID);
            getRDIDQuery.exec();
            getRDIDQuery.next();

            QString name;
            name.append(splittedText.value(i));
            name.append("<br>");
            name.append("Przystanek: " + startStopName);
            name.append("<br>");
            name.append(QString::fromUtf8("<i>Wejdź</i>"));
            routesDetailsModel->addRoute(RoutesItem(getRDIDQuery.record().value("id").toInt(), name, QString("")));

            continue;
        }

        if (!currentLine.contains("->"))
        {
            stopID = currentLine.toInt();
            lineID = splittedLine.value(i-1).split("->").value(0).toInt();
            routeID = splittedLine.value(i-1).split("->").value(1).toInt();

            getRDIDQuery.bindValue(":lineID", lineID);
            getRDIDQuery.bindValue(":routeID", routeID);
            getRDIDQuery.bindValue(":stopID", stopID);
            getRDIDQuery.exec();
            getRDIDQuery.next();

            QString name;
            name.append(splittedText.value(i-1));
            name.append("<br>");
            name.append("Przystanek: " + splittedText.value(i).remove("Przesiadka: "));
            name.append("<br>");
            name.append(QString::fromUtf8("<i>Wyjdź</i>"));
            routesDetailsModel->addRoute(RoutesItem(getRDIDQuery.record().value("id").toInt(), name, QString("")));
        }
        else
        {
            stopID = splittedLine.value(i-1).toInt();
            lineID = currentLine.split("->").value(0).toInt();
            routeID = currentLine.split("->").value(1).toInt();

            getRDIDQuery.bindValue(":lineID", lineID);
            getRDIDQuery.bindValue(":routeID", routeID);
            getRDIDQuery.bindValue(":stopID", stopID);
            getRDIDQuery.exec();
            getRDIDQuery.next();

            QString name;
            name.append(splittedText.value(i));
            name.append("<br>");
            name.append("Przystanek: " + splittedText.value(i-1).remove("Przesiadka: "));
            name.append("<br>");
            name.append(QString::fromUtf8("<i>Wejdź</i>"));
            routesDetailsModel->addRoute(RoutesItem(getRDIDQuery.record().value("id").toInt(), name, QString("")));
        }

        if (i == splittedLine.count() - 1)
        {
            stopID = endStopID;
            lineID = currentLine.split("->").value(0).toInt();
            routeID = currentLine.split("->").value(1).toInt();

            getRDIDQuery.bindValue(":lineID", lineID);
            getRDIDQuery.bindValue(":routeID", routeID);
            getRDIDQuery.bindValue(":stopID", stopID);
            getRDIDQuery.exec();
            getRDIDQuery.next();

            QString name;
            name.append(splittedText.value(i));
            name.append("<br>");
            name.append("Przystanek: " + endStopName);
            name.append("<br>");
            name.append(QString::fromUtf8("<i>Wyjdź</i>"));
            routesDetailsModel->addRoute(RoutesItem(getRDIDQuery.record().value("id").toInt(), name, QString("")));
            continue;
        }
    }
}

void Routes::routeDetailRowClicked(int routeDetailsID, QString routeIDs, QString route)
{
    timetable->clearData();
    timetable->getData(0, 0, 0, routeDetailsID);

    routesBox->setProperty("page", "TimetableB");
    searchDetailResultsBox->setVisible(false);
    routesTimetable->setVisible(true);
}
