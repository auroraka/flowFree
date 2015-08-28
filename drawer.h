#ifndef DRAWER_H
#define DRAWER_H

#include "gameinfo.h"
#include <QPaintDevice>
class Drawer
{

public:
    Drawer(QPaintDevice *device,GameInfo *game);
    void draw();//在device界面上按照game的信息绘制游戏界面
    void drawSource(QColor color,QPoint pos);
    QPainter *painter;


private:
    void drawGridding();//画网格线
    void drawBlocks();//画方块
    void drawWays();//画路径
    QPaintDevice *device;
    GameInfo *game;

};


#endif // DRAWER_H
