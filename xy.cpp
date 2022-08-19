#include "xy.h"

XY::XY(){c=QPoint(0,0);}

XY::~XY(){}

void XY::setXY(QPoint xy) {this->c=xy;}

void XY::setXY(XY xy)
{
    this->setXY(xy.x(),xy.y());
}

void XY::setXY(int xpos, int ypos) {setXY(QPoint(xpos,ypos));}

void XY::setX(int x) {this->c.setX(x);}

void XY::setY(int y) {this->c.setY(y);}

QPoint XY::xy() const {return this->c;}

int XY::x() const {return this->c.x();}

int XY::y() const {return this->c.y();}

void XY::addXY(QPoint xy) {this->c+=xy;}

void XY::addX(int x) {addXY(QPoint(x,0));}

void XY::addY(int y) {addXY(QPoint(0,y));}
