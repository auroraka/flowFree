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
    QPoint loc;
    int color;
    Status status;

    QRect getRect();
    QPoint getCenter();
    bool isNeighbour(const Block &a);
    bool isSame(const Block &a){return loc.x()==a.loc.x() && loc.y()==a.loc.y();}
    bool initBlock();
private:
};

#endif // BLOCK_H
