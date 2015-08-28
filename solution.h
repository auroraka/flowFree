#ifndef SOLUTION_H
#define SOLUTION_H

#include "gameinfo.h"
#include "enviroment.h"
#include "textinfo.h"

class Solution
{
public:
    Solution();
    TextInfo getSolution(const GameInfo &game);

private:
    void greedyAlgorithm();
    bool dfs(int colorID,QPoint pos,int step);
    bool inMap(int x,int y);
    bool fillAll();

    GameInfo game;
    QPoint pointRecord[maxColorTot][2];
    int colorRecord[maxColorTot];
    QPoint record[100];
};

#endif // SOLUTION_H
