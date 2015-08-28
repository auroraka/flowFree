#ifndef TEXTINFO_H
#define TEXTINFO_H

#include "gameinfo.h"

class TextInfo
{
public:
    int noSolution;//是否无解

    TextInfo();
    TextInfo(const GameInfo &game);//GameInfo转TextInfo
    bool transToGameInfo(GameInfo &game);//TextInfo转GameInfo
    bool openFile(QString fileDir);//打开游戏存档并载入信息
    bool saveFile(QString fileDir);//保存游戏到文件
    bool loadGame(int level,int id);//打开关卡(level-id.bak)
    void print();//打印TextInfo

private:
    int gameFormat;//游戏规模
    int map[15][15];//文本信息

    bool inMap(int x,int y);
    bool dfs(int x,int y,int num,GameInfo &game);
    bool checkColorLegal();
    bool checkWaysLegal(const GameInfo &game);
    bool haveGothrough(int x,int y);
};

#endif // TEXTINFO_H
