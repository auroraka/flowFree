#include "gameinfo.h"
#include "enviroment.h"

GameInfo::GameInfo()
{
    waysTot=0;
    sourceTot=0;
    nowWay=0;
    gameFormat=7;
}

int GameInfo::getLen(){
    return Height/gameFormat;
}
