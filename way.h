#ifndef WAY_H
#define WAY_H

#include "block.h"
#include <vector>
using std::vector;

//记录一条从起点到终点的路径
class Way
{
public:
    Way();
    vector<Block*> link;

    int size()const{return link.size();}//包含的Block个数
    int getColor()const{return (*link[0]).color;}//路径颜色
    Block& last(){return *link[link.size()-1];}//路径最后一个Block
    Block& head(){return *link[0];}//路径第一个Block
    void add(Block* a);//添加一个Block
    void clearTail();//去掉除头部的所有Block(比如路径被切断时)
    void initWay();//重置way
    void print();//打印way信息到qDebug
};


#endif // WAY_H
