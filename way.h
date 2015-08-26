#ifndef WAY_H
#define WAY_H

#include "block.h"
#include <vector>
using std::vector;

class Way
{
public:
    Way();
    vector<Block*> link;

    int size(){return link.size();}
    int getColor(){return (*link[0]).color;}
    Block& last(){return *link[link.size()-1];}
    Block& head(){return *link[0];}
    void add(Block* a){link.push_back(a);}
    void initWay();
    void clearTail();

private:
};

#endif // WAY_H
