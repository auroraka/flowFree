#include "block.h"
#include <QDebug>

Block::Block()
{
    rect=QRect(0,0,0,0);
    loc=QPoint(0,0);
    color=0;
    status=unmark;

}

bool Block::isNeighbour(const Block &a){
    //qDebug()<<"isNeighbour: "<<loc<<" "<<a.loc<<" -> "<<abs(loc.x()-a.loc.x())+abs(loc.y()-a.loc.y());
    return (abs(loc.x()-a.loc.x())+abs(loc.y()-a.loc.y())==1);
}

bool Block::initBlock(){
    rect=QRect(0,0,0,0);
    color=0;
    loc=QPoint(0,0);
    status=unmark;
}
