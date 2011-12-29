#ifndef LINESDETAILSITEM_H
#define LINESDETAILSITEM_H

#include <QtCore/QString>

class LinesDetailsItem
{
private:
    QString dayName;
    QString timetable;
    QString timetableLegend;

public:
    LinesDetailsItem(const QString dayName, const QString timetable, const QString timetableLegend);
    QString getDayName() const { return dayName; }
    QString getTimetable() const { return timetable; }
    QString getTimetableLegend() const { return timetableLegend; }
};

#endif // LINESDETAILSITEM_H
