#include "rojamodel.h"
#include <QtSql/QSqlRecord>
#include <QDebug>

RojaModel::RojaModel(QObject *parent, QSqlDatabase database) : QSqlTableModel(parent, database)
{
}

RojaModel::~RojaModel() {}

QVariant RojaModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
    {
        return QVariant();
    }
    QSqlTableModel model;

    model.setTable(this->tableName());
    if (!this->filter().isEmpty())
    {
        model.setFilter(this->filter());
    }
    model.select();
    while (model.canFetchMore())
    {
        model.fetchMore();
    }

    if (index.row() >= model.rowCount())
    {
       return  QString("");
    }

    QSqlRecord record = model.record(index.row());
    return record.value(QString(roles.value(role)));
}

void RojaModel::generateRoleNames()
{
    roles.clear();

    for (int i = 0; i < this->columnCount(); ++i)
    {
        roles[Qt::UserRole + i] = this->headerData(i, Qt::Horizontal).toByteArray();
    }

    setRoleNames(roles);
}
