#ifndef TEXTINFO_H
#define TEXTINFO_H

#include "gameinfo.h"

class TextInfo
{
public:
    TextInfo();
    TextInfo(const GameInfo &game);
    bool transToGameInfo(GameInfo &game);
    bool openFile(QString fileDir);
    bool saveFile(QString fileDir);
    void print();
    bool loadGame(int level,int id);

    int noSolution;
private:
    bool inMap(int x,int y);
    bool dfs(int x,int y,int num,GameInfo &game);
    bool checkColorLegal();
    bool checkWaysLegal(const GameInfo &game);
    bool haveGothrough(int x,int y);

    int gameFormat;
    int map[15][15];
};

#endif // TEXTINFO_H
