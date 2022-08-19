#ifndef COLOR_H
#define COLOR_H

#include <QtGlobal>
#include <QBrush>

#define Cyan QBrush(Qt::darkCyan)
#define Blue QBrush(Qt::darkBlue)
//#define Orange QBrush(QColor(255,165,0))
#define Orange QBrush(QColor(220,87,42))
#define Yellow QBrush(Qt::darkYellow)
#define Green QBrush(Qt::darkGreen)
#define Purple QBrush(QColor(160,32,240))
#define Red QBrush(Qt::darkRed)
#define Transparent QBrush(Qt::transparent)

//#define Cyan QBrush(Qt::cyan)
//#define Blue QBrush(Qt::blue)
//#define Orange QBrush(QColor(255,165,0))
//#define Yellow QBrush(Qt::yellow)
//#define Green QBrush(Qt::green)
//#define Purple QBrush(QColor(160,32,240))
//#define Red QBrush(Qt::red)
//#define Transparent QBrush(Qt::transparent)

namespace Color
{
enum Type
{
    cyan,
    blue,
    orange,
    yellow,
    green,
    purple,
    red
};
const QBrush Color[]=
{
    Cyan,       // cyan I
    Blue,       // blue J
    Orange,     // orange L
    Yellow,     // yellow O
    Green,      // green S
    Purple,     // purple T
    Red         // red Z
};
}

#endif // COLOR_H
