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
    now->show();
    if (old!=NULL){
        int x=old->x()+9,y=old->y()+38,width=old->width(),height=old->height();
        qDebug()<<"Interface pos: "<<x<<" "<<y<<" "<<width<<" "<<height;
        now->setGeometry(x,y,width,height);
        old->hide();
    }
    qDebug()<<"switcher switch to: "<<name;
}
