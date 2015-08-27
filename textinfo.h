#ifndef TEXTINFO_H
#define TEXTINFO_H

#include "gameinfo.h"

class TextInfo
{
public:
    TextInfo(const GameInfo &game);
    bool transToGameInfo(GameInfo &game);

private:
    bool inMap(int x,int y);
    bool dfs(int x,int y,int num,GameInfo &game);
    bool checkColorLegal();
    bool checkWaysLegal(const GameInfo &game);

    int gameFormat;
    int map[15][15];
};

#endif // TEXTINFO_H
