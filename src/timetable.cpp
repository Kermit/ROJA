#include "timetable.h"

#include <QtSql/QSqlQuery>
#include <QtSql/QSqlRecord>
#include "src/rojadatabase.h"

Timetable::Timetable(QObject *parent) :
    QObject(parent)
{
    model = new LinesDetailsModel(this);
}

void Timetable::getData(int stopID, int lineID, int routeID, int routeDetailsID)
{
    QString queryString("SELECT days.name AS dayName, times.time AS timeTable, times.legend AS timetableLegend"
                        " FROM times LEFT JOIN days ON times.dayID = days.id"
                        " WHERE times.routeDetailsID = " + QString::number(routeDetailsID));

    QSqlQuery query(queryString, RojaDatabase::getInstance()->getDatabase());
    int dayNameColumn = query.record().indexOf("dayName");
    int timetableColumn = query.record().indexOf("timeTable");
    int timetableLegendColumn = query.record().indexOf("timetableLegend");

    QString dayName;
    QString timetable;
    QString timetableLegend = "" ;

    text = "";

    while (query.next())
    {
        dayName = query.value(dayNameColumn).toString();

        timetable = query.value(timetableColumn).toString();
        timetable = timetable.replace(",", "</sup> <b>");
        timetable = "<b>" + timetable;
        timetable = timetable.replace(":", "</b><sup>");
        timetable = timetable.replace(";", " ");

        if (timetableLegend.isEmpty())
        {
            timetableLegend = query.value(timetableLegendColumn).toString();
            timetableLegend = timetableLegend.replace(";", "\n");
        }

        model->addTimetable(LinesDetailsItem(dayName, timetable, timetableLegend));
        text += dayName + "<br>" + timetable + "<br>" + timetableLegend + "<br>";
    }
}

LinesDetailsModel* Timetable::getModel()
{
    return model;
}

void Timetable::clearData()
{
    model->clearData();
}
