#ifndef ROJADATABASE_H
#define ROJADATABASE_H

#include <QtSql/QSqlDatabase>

class RojaDatabase
{
private:
    static RojaDatabase *instance;

    QSqlDatabase rojaDatabase;
    explicit RojaDatabase();
    RojaDatabase(const RojaDatabase&);
    RojaDatabase& operator=(const RojaDatabase&);

public:    
    static RojaDatabase* getInstance();

    ~RojaDatabase();
    bool openDatabase();
    QSqlDatabase getDatabase();
};

#endif // ROJADATABASE_H
