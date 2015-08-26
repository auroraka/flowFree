#include "drawer.h"
#include "enviroment.h"
#include <QPainter>

Drawer::Drawer(QPaintDevice *device,GameInfo *game):device(device),game(game)
{

}



//------------------------drawPart------------------------------
void Drawer::drawGridding(){
    QPainter painter(device);
    painter.setRenderHint(QPainter::Antialiasing, true);
    QPen *pen = new QPen(QColor(210,113,4));
    pen->setWidth(penLen);
    painter.setPen(*pen);
    int len=game->getLen();
    for (int i=0;i<=game->gameFormat;i++){
        painter.drawLine(QPoint(startX+i*len,startY),QPoint(startX+i*len,startY+Height));
    }
    for (int i=0;i<=game->gameFormat;i++){
        painter.drawLine(QPoint(startX,startY+i*len),QPoint(startX+Weight,startY+i*len));
    }
}

void Drawer::drawBlocks(){
    QPainter painter(device);
    painter.setRenderHint(QPainter::Antialiasing, true);
    for (int i=1;i<=game->gameFormat;i++){
        for (int j=1;j<=game->gameFormat;j++){
            QColor color=myColor[game->blocks[i][j].color];
            QBrush brush(color);
            if (game->blocks[i][j].status != unmark){
                brush.setColor(QColor(color.red()*0.5,color.green()*0.5,color.blue()*0.5));
            }
            painter.setBrush(brush);
            //qDebug()<<i<<" "<<j<<" "<<blocks[i][j].rect;
            painter.drawRect(game->blocks[i][j].rect);

            //brush.setColor(color);
            //painter.setBrush(color);
            if (game->blocks[i][j].status == source){
                //qDebug()<<"source: "<<i<<" "<<j<<" "<<blocks[i][j].color;
                QPen pen(color);
                painter.setPen(pen);
                brush.setColor(color);
                painter.setBrush(brush);
                int len=30;
                QPoint pos=game->blocks[i][j].getCenter();
                painter.drawEllipse(pos.x()-len,pos.y()-len,len*2,len*2);
            }
        }
    }
}

void Drawer::drawWays(){
    QPainter painter(device);
    painter.setRenderHint(QPainter::Antialiasing, true);
    QPen pen;
    pen.setWidth(20);
    pen.setStyle(Qt::SolidLine);
    pen.setCapStyle(Qt::SquareCap);
    for (int i=1;i<=game->waysTot;i++) if (game->ways[i].size()>1){
        pen.setColor(myColor[game->ways[i].getColor()]);
        painter.setPen(pen);
        for (int j=1;j<game->ways[i].size();j++){
            //qDebug()<<"draw ways: "<<ways[i].link[j-1].loc<<"->"<<ways[i].link[j].loc<<" color: "<<ways[i].link[j-1].color<<" "<<ways[i].link[j].color;
            painter.drawLine(game->ways[i].link[j-1]->getCenter(),game->ways[i].link[j]->getCenter());
        }
    }
}
void Drawer::draw(){
    drawBlocks();
    drawGridding();
    drawWays();

}
