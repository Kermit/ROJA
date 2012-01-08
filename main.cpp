#include <QtGui/QApplication>
#include <QtCore/QTextCodec>

#include <QtDeclarative/QDeclarativeItem>

#include "qmlapplicationviewer.h"
#include "src/rojadatabase.h"
#include "src/model/rojamodel.h"

#include "qmlapplicationviewer.h"
#include "src/mainwindow.h"

#include <QDebug>
#include <QFontDialog>

Q_DECL_EXPORT int main(int argc, char *argv[])
{    
    QApplication::addLibraryPath("/data/data/org.kde.necessitas.ministro/files/qt/plugins");
    QScopedPointer<QApplication> app(createApplication(argc, argv));
    QScopedPointer<QmlApplicationViewer> viewer(QmlApplicationViewer::create());

    qApp->setFont(QFont("Droid Serif"));

    viewer->setOrientation(QmlApplicationViewer::ScreenOrientationLockPortrait);
    viewer->setResizeMode(QmlApplicationViewer::SizeRootObjectToView);
    viewer->setMainQmlFile(QLatin1String("qml/roja/main.qml"));
    viewer->showExpanded();

    MainWindow mainWindow(qApp, viewer.data());
    return app->exec();
}
