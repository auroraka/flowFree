#ifndef ENVIROMENT_H
#define ENVIROMENT_H

#include <QColor>
#include <QWidget>
#include <QPoint>

//source圆点的半径
static const int sourceWide=30;
//游戏界面的左上坐标
static const int startX=30,startY=50;//坐标为(y,x),其中x为坐标轴x轴正方向,y为坐标轴y轴负方向
//游戏界面小格宽度
static const int BlockLen=100;
//网格线宽度
static const int penLen=2;
//设计界面8个待选颜色左上坐标
static const int selectionStartX=730,selectionStartY=250;
//设计界面8个待选颜色间距
static const int selectionLen=100;


//总颜色数
static const int myColorTot = 11;
static const int maxColorTot=20;
static const QColor myColor[15]={
    QColor(0,0,0),//黑 1
    QColor(255,0,0),//红 2
    QColor(0,128,0),//绿 3
    QColor(0,0,255),//蓝 4
    QColor(255,128,0),//橙 5
    QColor(128,64,0),//棕 10
    QColor(255,255,0),//黄 6
    QColor(0,255,255),//青 7
    QColor(255,0,255),//粉 8
    QColor(128,0,255),//紫 9
    QColor(128,128,0),//屎黄 11
    QColor(192,192,193),//灰 12

};
static const int xo[]={0,0,1,-1};
static const int yo[]={1,-1,0,0};

#endif // ENVIROMENT

