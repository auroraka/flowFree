#include "drawer.h"
#include "enviroment.h"
#include <QPainter>
#include <QDebug>

QPoint Offset;

Drawer::Drawer(GameInfo *game):game(game)
{
}
void Drawer::drawSource(QColor color,QPoint pos){
    QPen pen(color);
    painter->setPen(pen);
    QBrush brush(color);
    painter->setBrush(brush);
    int len=sourceWide;
    //qDebug()<<"draw circle: "<<pos.x()-len<<" "<<pos.y()-len<<" "<<len*2,len*2;
    painter->drawEllipse(Offset.x()+pos.x()-len,Offset.y()+pos.y()-len,len*2,len*2);
}


//------------------------drawPart------------------------------
void Drawer::drawGridding(){
    painter->setRenderHint(QPainter::Antialiasing, true);
    QPen *pen = new QPen(QColor(210,113,4));
    pen->setWidth(penLen);
    painter->setPen(*pen);
    int gameLen=BlockLen*game->gameFormat;
    for (int i=0;i<=game->gameFormat;i++){
        painter->drawLine(Offset+QPoint(startY+i*BlockLen,startX),Offset+QPoint(startY+i*BlockLen,startX+gameLen));
    }
    for (int i=0;i<=game->gameFormat;i++){
        painter->drawLine(Offset+QPoint(startY,startX+i*BlockLen),Offset+QPoint(startY+gameLen,startX+i*BlockLen));
    }
}


void Drawer::drawBlocks(){
    painter->setRenderHint(QPainter::Antialiasing, true);
    for (int i=1;i<=game->gameFormat;i++){
        for (int j=1;j<=game->gameFormat;j++){



            QColor color=myColor[game->blocks[i][j].color];
            QBrush brush(QColor(0,0,0));
            QRect rect=game->blocks[i][j].getRect();

            if (game->blocks[i][j].status != unmark){
                brush.setColor(QColor(color.red()*0.5,color.green()*0.5,color.blue()*0.5));
            }
            painter->setBrush(brush);

            if (game->style ==1 ) painter->drawRect(QRect(Offset+QPoint(rect.x(),rect.y()),QSize(rect.size())));

            if (game->blocks[i][j].status == source){
                drawSource(color,game->blocks[i][j].getCenter());
            }
        }
    }
}

void Drawer::drawWays(){
    QPen pen;
    pen.setWidth(WayLen);
    pen.setStyle(Qt::SolidLine);
    pen.setCapStyle(Qt::RoundCap);
    for (int i=1;i<=game->waysTot;i++) if (game->ways[i].size()>1){
        pen.setColor(myColor[game->ways[i].getColor()]);
        painter->setPen(pen);
        for (int j=1;j<game->ways[i].size();j++){
            painter->drawLine(Offset+game->ways[i].link[j-1]->getCenter(),Offset+game->ways[i].link[j]->getCenter());
        }
    }
}
void Drawer::drawMouse(){
    QColor color=myColor[game->mouseColor];
    color=QColor(color.red()*0.8,color.green()*0.8,color.blue()*0.8,128);
    QPen pen(color);
    QBrush brush(color);
    painter->setPen(pen);
    painter->setBrush(brush);
    painter->drawEllipse(game->mousePos,BlockLen/2,BlockLen/2);
}

void Drawer::draw(){
    painter->setRenderHint(QPainter::Antialiasing, true);

    QPoint nowCenter(startY+BlockLen*game->gameFormat/2,startX+BlockLen*game->gameFormat/2);
    Offset=QPoint(0,0);//GameCenter-nowCenter;
    QPoint offset=GameCenter-nowCenter;
    startX+=offset.x();startY+=offset.y();

    if (game->isTracking && game->style==0) drawMouse();
    drawBlocks();
    drawGridding();
    drawWays();
}
