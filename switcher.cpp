#include "switcher.h"
#include <QDebug>

Switcher::Switcher()
{
    now=NULL;
    qDebug()<<"switcher maked";
}

void Switcher::add(QString name, QWidget *interface){
    qDebug()<<"switcher add: "<<QString(name);
    switcher[name]=interface;
}
void Switcher::showInterface(QString name){
    if (switcher.find(name)==switcher.end()){
        qDebug()<<"switcher ERROR: ["<<name<<"] not found.";
        return;
    }
    QWidget *old=now;
    now = switcher[name];
    if (old!=NULL){
        int x=old->x(),y=old->y(),width=old->width(),height=old->height();
        now->setGeometry(x,y,width,height);
        old->hide();
    }
    now->show();
    qDebug()<<"switcher switch to: "<<name;
}
