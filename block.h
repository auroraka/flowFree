#ifndef BLOCK_H
#define BLOCK_H

#include <QColor>
#include <QRect>
#include <QPoint>

enum Status{gothrough,source,unmark};

class Block
{
public:
    Block();
    QPoint loc;//坐标
    int color;//颜色
    Status status;//状态 status={source,gothrough,unmark}

    QRect getRect();//Block所在的矩形框坐标
    QPoint getCenter();//中心坐标
    bool isNeighbour(const Block &a);//和某一个Block处于游戏界面相邻位置
    bool isSame(const Block &a){return loc.x()==a.loc.x() && loc.y()==a.loc.y();}
    bool initBlock();//重置Block信息
};



#endif // BLOCK_H
