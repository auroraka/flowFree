#ifndef DATABASE_H
#define DATABASE_H


#include <QSqlDatabase>
#include <QSqlQuery>

class Database
{
public:
    Database();
    void addAcievement(int level,int id);
    void moveAchievement(int level,int id);
    //DatabaseType getAllAchievement();
    bool haveAchievement(int level, int id);

private:
    QSqlDatabase db;
    QSqlQuery query;
    void createTable();
};


extern Database database;
#endif // DATABASE_H
