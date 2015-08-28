#include "drawer.h"
#include "enviroment.h"
#include <QPainter>
#include <QDebug>

Drawer::Drawer(QPaintDevice *device,GameInfo *game):device(device),game(game)
{
    //painter = new QPainter(device);
}
void Drawer::drawSource(QColor color,QPoint pos){
    //return;
    //qDebug()<<"painter device: "<<painter->device();
    //qDebug()<<"drawSource: "<<color<<" "<<pos;
    //return;
    QPen pen(color);
    painter->setPen(pen);
    QBrush brush(color);
    painter->setBrush(brush);
    int len=sourceWide;
    //qDebug()<<"draw circle: "<<pos.x()-len<<" "<<pos.y()-len<<" "<<len*2,len*2;
    painter->drawEllipse(pos.x()-len,pos.y()-len,len*2,len*2);
}


//------------------------drawPart------------------------------
void Drawer::drawGridding(){
    painter->setRenderHint(QPainter::Antialiasing, true);
    QPen *pen = new QPen(QColor(210,113,4));
    pen->setWidth(penLen);
    painter->setPen(*pen);
    int gameLen=BlockLen*game->gameFormat;
    for (int i=0;i<=game->gameFormat;i++){
        painter->drawLine(QPoint(startY+i*BlockLen,startX),QPoint(startY+i*BlockLen,startX+gameLen));
    }
    for (int i=0;i<=game->gameFormat;i++){
        painter->drawLine(QPoint(startY,startX+i*BlockLen),QPoint(startY+gameLen,startX+i*BlockLen));
    }
}


void Drawer::drawBlocks(){
    painter->setRenderHint(QPainter::Antialiasing, true);
    for (int i=1;i<=game->gameFormat;i++){
        for (int j=1;j<=game->gameFormat;j++){
            QColor color=myColor[game->blocks[i][j].color];
            QBrush brush(color);
            if (game->blocks[i][j].status != unmark){
                brush.setColor(QColor(color.red()*0.5,color.green()*0.5,color.blue()*0.5));
            }
            painter->setBrush(brush);
            //qDebug()<<i<<" "<<j<<" "<<blocks[i][j].rect;
            painter->drawRect(game->blocks[i][j].getRect());

            //brush.setColor(color);
            //painter.setBrush(color);
            if (game->blocks[i][j].status == source){
                drawSource(color,game->blocks[i][j].getCenter());
            }
        }
    }
}

void Drawer::drawWays(){
    painter->setRenderHint(QPainter::Antialiasing, true);
    QPen pen;
    pen.setWidth(20);
    pen.setStyle(Qt::SolidLine);
    pen.setCapStyle(Qt::SquareCap);
    for (int i=1;i<=game->waysTot;i++) if (game->ways[i].size()>1){
        pen.setColor(myColor[game->ways[i].getColor()]);
        painter->setPen(pen);
        for (int j=1;j<game->ways[i].size();j++){
            //qDebug()<<"draw ways: "<<ways[i].link[j-1].loc<<"->"<<ways[i].link[j].loc<<" color: "<<ways[i].link[j-1].color<<" "<<ways[i].link[j].color;
            painter->drawLine(game->ways[i].link[j-1]->getCenter(),game->ways[i].link[j]->getCenter());
        }
    }
}
void Drawer::draw(){
    drawBlocks();
    drawGridding();
    drawWays();
}
