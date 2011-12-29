#ifndef TIMETABLE_H
#define TIMETABLE_H

#include <QtCore/QObject>
#include "src/model/linesdetailsmodel.h"

class Timetable : public QObject
{
    Q_OBJECT
private:
    LinesDetailsModel *model;

public:
    explicit Timetable(QObject *parent = 0);
    void getData(int stopID, int lineID, int routeID, int routeDetailsID);
    LinesDetailsModel* getModel();
    QString text;
    void clearData();
};

#endif // TIMETABLE_H
