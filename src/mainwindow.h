#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtCore/QObject>
#include <QtCore/QList>

#include "qmlapplicationviewer.h"

class QDeclarativeItem;
class Page;
class Stops;
class Lines;
class Favs;
class Routes;

class MainWindow : public QObject
{
    Q_OBJECT

private:
    QmlApplicationViewer *viewer;
    QList<QDeclarativeItem*> mainButtonsList;
//    QDeclarativeItem *favsButton;
    QDeclarativeItem *linesButton;
    QDeclarativeItem *stopsButton;
    QDeclarativeItem *routesButton;
    QDeclarativeItem *exitButton;
    QList<Page*> loadersList;
    Stops *stops;
    Lines *lines;
    Favs *favs;
    Routes *routes;

public:
    explicit MainWindow(QObject *parent = 0, QmlApplicationViewer *applicationViewer = 0);

private slots:
//    void favsButtonClicked();
    void linesButtonClicked();
    void stopsButtonClicked();
    void routesButtonClicked();
    void exitButtonClicked();
};

#endif // MAINWINDOW_H
