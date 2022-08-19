#ifndef DIRECTION_H
#define DIRECTION_H

#include <QPoint>

namespace Direction
{

enum Type
{
    UP,
    DOWN,
    LEFT,
    RIGHT
};

static constexpr QPoint Move[]=
{
    QPoint(0,1),
    QPoint(0,-1),
    QPoint(-1,0),
    QPoint(1,0)
};

}

#endif // DIRECTION_H
