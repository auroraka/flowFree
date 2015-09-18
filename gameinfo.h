#ifndef GAMEINFO_H
#define GAMEINFO_H

#include "block.h"
#include "way.h"

class GameInfo
{
public:
    Block blocks[15][15];
    int map[15][15];
    Way ways[50];
    int waysTot;//ways总数
    int gameFormat; //游戏大小(5*5 6*6 7*7)
    int noSolution;//游戏无解
    int sourceTot;//源点总数
    int nowWay;
    QPoint mousePos;//鼠标位置
    int mouseColor;
    bool isTracking;//追踪状态(鼠标按下)
    int focusWay;//追踪的路径编号
    int style;


    GameInfo();
    void makeBlocksInfo();//根据gameFormat初始化Block信息(如坐标位置等)
    void clearWay(int);//去除某条way
    void cutWay(int);//切断某条way
    bool isLegal();
    void makeColor(int &color);
    void makePos(int &x,int &y);
    void makeSource();//随机生成源点(用于随机地图)
    void reInit();//重置GameInfo(清空)
    void restart();//重新开始游戏(保留源点)
    bool getLoc(int &a,int &b,QPoint pos);
    bool legalDesign();//不合法的GameInfo
    void print();//打印GameInfo
    void getGodMode();
private:
    int godMode;
};




#endif // GAMEINFO_H
