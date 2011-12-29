#ifndef LINES_H
#define LINES_H

#include <QtCore/QObject>
#include <QtDeclarative/QDeclarativeItem>

#include "src/page.h"
#include "qmlapplicationviewer.h"

class LinesModel;
class LinesStopsModel;
class LinesDetailsModel;
class Timetable;

class Lines : public Page
{
    Q_OBJECT

private:
    QmlApplicationViewer *viewer;
    QDeclarativeItem *linesSection;
    QDeclarativeItem *linesTitleBar;
    QDeclarativeItem *linesLoader;
    QDeclarativeItem *linesListView;
    QDeclarativeItem *linesContent;
    QDeclarativeItem *linesStopsBox;
    QDeclarativeItem *linesStopsContent;
    QDeclarativeItem *linesStopsLoader;
    QDeclarativeItem *linesStopsListView;
    QDeclarativeItem *linesDetailsContent;
    QDeclarativeItem *linesDetailsLoader;

    QDeclarativeItem *backButton;
    QDeclarativeItem *searchButton;
    QDeclarativeItem *searchLine;

    LinesModel *model;
    LinesStopsModel *stopsModel;
    LinesDetailsModel *detailsModel;
    Timetable *timetable;

    QString currentLineNumber;
    QString currentWayName;

    void init();
    void getData(QString filter);
    void getStopsListData(int lineID, int routeID);

public:
    explicit Lines(QObject *parent = 0, QmlApplicationViewer *applicationViewer = 0);
    virtual ~Lines();

    void show();
    void hide();

private slots:
    void lineRowClicked(int lineID, int routeID, QString lineNumber, QString lineWayName);
    void lineStopRowClicked(int lineID, int routeID, int stopID, QString stopName, int routesDetailsID);
    void backButtonClicked(QString page);
    void searchButtonClicked();
    void filter(QString text);
};

#endif // LINES_H
