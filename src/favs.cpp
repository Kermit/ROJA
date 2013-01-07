#include "favs.h"

Favs::Favs(QObject *parent, QmlApplicationViewer *applicationViewer) :
    Page(parent)
{
    viewer = applicationViewer;
    favsLoader = viewer->rootObject()->findChild<QDeclarativeItem *>("favsLoader");
    favsLoader->setProperty("source", "assets:/qml/roja/Favs.qml");
}

Favs::~Favs() {}

void Favs::show()
{
    favsLoader->setProperty("visible", "true");
}

void Favs::hide()
{
    favsLoader->setProperty("visible", false);
}
