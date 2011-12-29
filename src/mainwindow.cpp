#include "mainwindow.h"

#include <QtGui/QApplication>
#include <QtDeclarative/QDeclarativeContext>
#include <QtDeclarative/QDeclarativeItem>
#include <QDesktopWidget>

#include "src/rojadatabase.h"
#include "src/page.h"
#include "src/stops.h"
#include "src/lines.h"
#include "src/favs.h"
#include "src/routes.h"
#include "src/model/rojamodel.h"

#include <QDebug>

MainWindow::MainWindow(QObject *parent, QmlApplicationViewer *applicationViewer) :
    QObject(parent)
{
    viewer = applicationViewer;    

    //favsButton = viewer->rootObject()->findChild<QDeclarativeItem *>("favsButton");
    linesButton = viewer->rootObject()->findChild<QDeclarativeItem *>("linesButton");
    stopsButton = viewer->rootObject()->findChild<QDeclarativeItem *>("stopsButton");
    routesButton = viewer->rootObject()->findChild<QDeclarativeItem *>("routesButton");
    exitButton = viewer->rootObject()->findChild<QDeclarativeItem *>("exitButton");
    //mainButtonsList.append(favsButton);
    mainButtonsList.append(linesButton);
    mainButtonsList.append(stopsButton);
    mainButtonsList.append(routesButton);
    mainButtonsList.append(exitButton);

    //connect(favsButton, SIGNAL(clicked()), this, SLOT(favsButtonClicked()));
    connect(linesButton, SIGNAL(clicked()), this, SLOT(linesButtonClicked()));
    connect(stopsButton, SIGNAL(clicked()), this, SLOT(stopsButtonClicked()));
    connect(routesButton, SIGNAL(clicked()), this, SLOT(routesButtonClicked()));
    connect(exitButton, SIGNAL(clicked()), this, SLOT(exitButtonClicked()));

    lines = 0;
    stops = 0;
    routes = 0;
    favs = 0;
    RojaDatabase::getInstance()->openDatabase();
    lines = new Lines(this, viewer);
    loadersList.append(lines);
    lines->show();
}

//void MainWindow::favsButtonClicked()
//{
//    foreach (QDeclarativeItem *item, mainButtonsList)
//    {
//        item->setProperty("state", "disable");
//    }

//    favsButton->setProperty("state", "enable");

//    foreach (Page *item, loadersList)
//    {
//        item->hide();
//    }

//    if (favs == NULL)
//    {
//        favs = new Favs(this, viewer);
//        loadersList.append(favs);
//    }

//    favs->show();
//}

void MainWindow::linesButtonClicked()
{
    foreach (QDeclarativeItem *item, mainButtonsList)
    {
        item->setProperty("state", "disable");
    }

    linesButton->setProperty("state", "enable");

    foreach (Page *item, loadersList)
    {
        item->hide();
    }

    if (lines == NULL)
    {
        lines = new Lines(this, viewer);
        loadersList.append(lines);
    }

    lines->show();
}

void MainWindow::stopsButtonClicked()
{
    foreach (QDeclarativeItem *item, mainButtonsList)
    {
        item->setProperty("state", "disable");
    }

    stopsButton->setProperty("state", "enable");

    foreach (Page *item, loadersList)
    {
        item->hide();
    }

    if (stops == NULL)
    {
        stops = new Stops(this, viewer);
        loadersList.append(stops);
    }
    stops->show();
}

void MainWindow::routesButtonClicked()
{
    foreach (QDeclarativeItem *item, mainButtonsList)
    {
        item->setProperty("state", "disable");
    }

    routesButton->setProperty("state", "enable");

    foreach (Page *item, loadersList)
    {
        item->hide();
    }

    if (routes == NULL)
    {
        routes = new Routes(this, viewer);
        loadersList.append(routes);
    }

    routes->show();
}

void MainWindow::exitButtonClicked()
{
    foreach (QDeclarativeItem *item, mainButtonsList)
    {
        item->setProperty("state", "disable");
    }

    exitButton->setProperty("state", "enable");

    qApp->exit(0);
}
