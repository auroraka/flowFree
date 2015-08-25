#ifndef BLOCK_H
#define BLOCK_H

#include <QColor>
#include <QRect>

class Block
{
public:
    Block(QRect rect = QRect(0,0,0,0),QColor color = QColor(0,0,0));
    QRect rect;
    QColor color;
};

#endif // BLOCK_H
