#ifndef FAVS_H
#define FAVS_H

#include <QtCore/QObject>
#include <QtDeclarative/QDeclarativeItem>

#include "src/page.h"
#include "qmlapplicationviewer.h"

class Favs : public Page
{
private:
    QmlApplicationViewer *viewer;
    QDeclarativeItem *favsLoader;

public:
    explicit Favs(QObject *parent = 0, QmlApplicationViewer *applicationViewer = 0);
    virtual ~Favs();
    void show();
    void hide();
};

#endif // FAVS_H
