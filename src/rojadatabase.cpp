#include "rojadatabase.h"
#include <QDebug>
#include <QFile>
#include <QtSql/QSqlError>
#include <QtGui/QFileDialog>
#include <QSqlQuery>

RojaDatabase::RojaDatabase()
{
    rojaDatabase = QSqlDatabase::addDatabase("QSQLITE");
    rojaDatabase.setDatabaseName("/sdcard/RojaDatabase.db.sqlite");
}

RojaDatabase::~RojaDatabase() {}

RojaDatabase* RojaDatabase::getInstance()
{
    if (instance == NULL)
    {
        instance = new RojaDatabase();
    }

    return instance;
}

bool RojaDatabase::openDatabase()
{
    bool result = false;
    result = rojaDatabase.open();

    QFile file("content/roja/RojaDatabase.db.sqlite");
    return result;
}

QSqlDatabase RojaDatabase::getDatabase()
{
    return rojaDatabase;
}

RojaDatabase* RojaDatabase::instance = 0;
