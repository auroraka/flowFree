#include "way.h"
#include <QDebug>
Way::Way()
{
    link.clear();
}

void Way::initWay(){
    link.clear();
}

void Way::clearTail(){
    for (int i=0;i<link.size();i++){
        if (link[i]->status == gothrough){
            link[i]->status = unmark;
            link[i]->color=0;
            qDebug()<<"change "<<link[i]->loc<<" from gothrough to unmark";
        }
    }
    Block* temp = link[0];
    link.clear();
    link.push_back(temp);
}
void Way::add(Block *a){
    //qDebug()<<"add block: "<<a->loc;
    link.push_back(a);
}

void Way::print(){
    QString info;
    QTextStream stream(&info);
    stream<<"way: ";
    for (int i=0;i<link.size();i++){
        stream<<"("<<link[i]->loc.x()<<link[i]->loc.y()<<")";
    }
    qDebug()<<info;
}
