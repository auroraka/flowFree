#include "database.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>

Database::Database()
{
    db=QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("flowFree.db");
    if (!db.open()){
        qDebug()<<"[ERROR] database not open";
        return;
    }
    query = QSqlQuery(db);
    createTable();
    addAcievement(5,1);
    /*for (int i=5;i<=7;i++){
        for (int j=1;j<=7;j++){
            qDebug()<<i<<" "<<j<<" "<<haveAchievement(i,j);
        }
    }*/
   // qDebug()<<"aaa: "<<haveAchievement(5,1);

}

//query = QSqlQuery(db);
void Database::createTable(){
    qDebug()<<"create database";
    query.exec("create table achievement(level int primary key)");
}
void Database::addAcievement(int level, int id){
    qDebug()<<"insert into database: "<<level<<" "<<id;
    QString cmd;
    QTextStream(&cmd)<<"insert into achievement values("<<level*100+id<<")";
    query.exec(cmd);
}
void Database::moveAchievement(int level, int id){
    QString cmd;
    QTextStream(&cmd)<<"delete from achievement where level = "<<level*100+id;
    query.exec(cmd);
}

bool Database::haveAchievement(int level, int id){
    QString cmd;
    QTextStream(&cmd)<<"select * from achievement where level = "<<level*100+id;
    query.exec(cmd);
    if (query.next()){
        if (query.value(0).toInt()==level*100+id){
            return true;
        }
    }
    return false;
}

//DatabaseType Database::getAllAchievement(){
    /*DatabaseType databaseInfo;
    query.exec("select * from achievement");
    while (query.next()){
        //qDebug()<<query.value(0).toInt();
        databaseInfo.insert(pair<int,int>(query.value(0).toInt(),query.value(1).toInt()));
    }
    return databaseInfo;*/
//}

