#ifndef ROJAMODEL_H
#define ROJAMODEL_H

#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlTableModel>
#include <QtSql/QSqlRecord>
#include <QtCore/QVariant>

class RojaModel : public QSqlTableModel
{
    Q_OBJECT

private:
    QHash<int, QByteArray> roles;

public:
    RojaModel(QObject *parent = 0, QSqlDatabase database = QSqlDatabase());
    ~RojaModel();

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    void generateRoleNames();
};

#endif // ROJAMODEL_H
