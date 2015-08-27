#ifndef ENVIROMENT_H
#define ENVIROMENT_H

#include <QColor>
#include <QWidget>
#include <QPoint>

static const int startX=50,startY=50,Weight=700,Height=700;
static const int penLen=2;
static const int myColorTot = 10;
static const QColor myColor[15]={
    QColor(0,0,0),//黑 1
    QColor(255,0,0),//红 2
    QColor(0,255,0),//绿 3
    QColor(0,0,255),//蓝 4
    QColor(255,255,0),//黄 5
    QColor(0,255,255),//青 6
    QColor(255,0,255),//粉 7
    QColor(128,0,255),//紫 8
    QColor(128,64,0),//棕 9
    QColor(128,128,0),//屎黄 10

};
static const int xo[]={0,0,1,-1};
static const int yo[]={1,-1,0,0};

#endif // ENVIROMENT

