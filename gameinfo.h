#ifndef GAMEINFO_H
#define GAMEINFO_H

#include "block.h"
#include "way.h"

class GameInfo
{
public:
    GameInfo();
    int getLen();
    void makeBlocksInfo();
    void clearWay(int);
    void cutWay(int);
    bool isLegal();
    void makeColor(int &color);
    void makePos(int &x,int &y);
    void makeSource();

    Block blocks[15][15];
    int map[15][15];
    Way ways[50];
    int waysTot;
    int sourceTot;
    int nowWay;
    int gameFormat; 
};




#endif // GAMEINFO_H
