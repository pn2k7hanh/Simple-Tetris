#ifndef XY_H
#define XY_H

#include <QPoint>

class XY
{
public:
    XY();
    ~XY();
    void setXY(QPoint xy);
    void setXY(XY xy);
    void setXY(int xpos,int ypos);
    void setX(int x);
    void setY(int y);
    QPoint xy() const;
    int x() const;

    int y() const;
    void addXY(QPoint xy);
    void addX(int x);
    void addY(int y);
private:
    QPoint c;
};

#endif // XY_H
