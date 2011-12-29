#ifndef STOPS_H
#define STOPS_H

#include <QtCore/QObject>
#include <QtDeclarative/QDeclarativeItem>

#include "src/page.h"
#include "qmlapplicationviewer.h"

class StopsModel;
class LinesModel;
class LinesDetailsModel;
class Timetable;

class Stops : public Page
{
    Q_OBJECT

private:
    QmlApplicationViewer *viewer;
    QDeclarativeItem *stopsLoader;

    QDeclarativeItem *stopsSection;
    QDeclarativeItem *stopsTitleBar;
    QDeclarativeItem *stopsListView;
    QDeclarativeItem *stopsContent;
    QDeclarativeItem *stopsLinesContent;
    QDeclarativeItem *stopsLinesLoader;

    QDeclarativeItem *stopLinesBox;
    QDeclarativeItem *stopsLinesListView;
    QDeclarativeItem *slDetailsContent;
    QDeclarativeItem *slDetailsLoader;

    QDeclarativeItem *backButton;
    QDeclarativeItem *searchButton;
    QDeclarativeItem *searchLine;

    StopsModel *stopsModel;
    LinesModel *stopsLinesModel;
    LinesDetailsModel *detailsModel;
    Timetable *timetable;

    QString currentStop;

    void getData(QString text);
    void init();
    void getStopsLinesData(int stopID);

public:
    explicit Stops(QObject *parent = 0, QmlApplicationViewer *applicationViewer = 0);
    virtual ~Stops();
    void show();
    void hide();

private slots:
    void stopClicked(QString stopName, int stopID);
    void backButtonClicked(QString page);
    void searchButtonClicked();
    void stopLineRowClicked(QString lineNumber, QString lineWayName, int routesDetailsID);
    void filter(QString text);
};

#endif // STOPS_H
