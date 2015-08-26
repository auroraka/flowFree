#ifndef GAMEINFO_H
#define GAMEINFO_H

#include "block.h"
#include "way.h"

class GameInfo
{
public:
    GameInfo();
    Block blocks[15][15];
    int map[15][15];
    Way ways[50];
    int waysTot;
    int sourceTot;
    int nowWay;
    int gameFormat;
    int getLen();
};

#endif // GAMEINFO_H
