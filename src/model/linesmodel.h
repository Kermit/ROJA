#ifndef LINESMODEL_H
#define LINESMODEL_H

#include <QtCore/QAbstractListModel>
#include <QtCore/QList>
#include <QtCore/QtAlgorithms>

#include "src/model/linesitem.h"

class LinesModel : public QAbstractListModel
{
    Q_OBJECT

private:
    QList<LinesItem> items;

public:
    enum LinesRoles
    {
        IdRole = Qt::UserRole + 1,
        NumberRole,
        RouteIDRole,
        WayRole
    };

    explicit LinesModel(QObject *parent = 0);
    void addLine(const LinesItem item);
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    void sort();
    static bool compareNames(const LinesItem &s1, const LinesItem &s2);
    void clearData();
};

#endif // LINESMODEL_H
