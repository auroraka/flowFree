#include "block.h"
#include "enviroment.h"
#include <QDebug>

Block::Block()
{
    loc=QPoint(0,0);
    color=0;
    status=unmark;

}

bool Block::isNeighbour(const Block &a){
    //qDebug()<<"isNeighbour: "<<loc<<" "<<a.loc<<" -> "<<abs(loc.x()-a.loc.x())+abs(loc.y()-a.loc.y());
    return (abs(loc.x()-a.loc.x())+abs(loc.y()-a.loc.y())==1);
}

bool Block::initBlock(){
    color=0;
    loc=QPoint(0,0);
    status=unmark;
}
QPoint Block::getCenter(){
    QRect rect=getRect();
    return QPoint(rect.x()+rect.width()/2,rect.y()+rect.height()/2);
}
QRect Block::getRect(){
    return QRect(startY+BlockLen*(loc.y()-1),startX+BlockLen*(loc.x()-1),BlockLen,BlockLen);
}

