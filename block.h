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
    QRect rect;
    QPoint loc;
    int color;
    Status status;

    QPoint getCenter(){return QPoint(rect.x()+rect.width()/2,rect.y()+rect.height()/2);}
    bool isNeighbour(const Block &a);
    bool isSame(const Block &a){return loc.x()==a.loc.x() && loc.y()==a.loc.y();}
    bool initBlock();
private:
};

#endif // BLOCK_H
