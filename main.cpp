#include <QtGui/QApplication>
#include "qmlapplicationviewer.h"

Q_DECL_EXPORT int main(int argc, char *argv[])
{
    QScopedPointer<QApplication> app(createApplication(argc, argv));
    QScopedPointer<QmlApplicationViewer> viewer(QmlApplicationViewer::create());

    viewer->setOrientation(QmlApplicationViewer::ScreenOrientationAuto);
    viewer->setResizeMode(QmlApplicationViewer::SizeRootObjectToView);
    viewer->setMainQmlFile(QLatin1String("qml/roja/main.qml"));
    viewer->showExpanded();

    return app->exec();
}
