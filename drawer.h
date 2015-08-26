#ifndef DRAWER_H
#define DRAWER_H

#include "gameinfo.h"
#include <QPaintDevice>
class Drawer
{

public:
    Drawer(QPaintDevice *device,GameInfo *game);
    void draw();

private:
    void drawGridding();
    void drawBlocks();
    void drawWays();
    QPaintDevice *device;
    GameInfo *game;

};

#endif // DRAWER_H
