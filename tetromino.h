#ifndef TETROMINO_H
#define TETROMINO_H

#include <QGraphicsItem>
#include <QDebug>
#include "color.h"
#include "block.h"
#include "xy.h"

class Tetromino : public QGraphicsItem
{
public:
    enum Type
    {
        i, // 0
        j, // 1
        l, // 2
        o, // 3
        s, // 4
        t, // 5
        z,  // 6
        NONE
    };
private:
    class Bl : public Block, public XY
    {
    public:
        void setBl(Bl &bl)
        {
            this->setBlock(bl);
            this->setXY(bl);
        }
    };
public:
    Tetromino();
    Tetromino(Tetromino::Type type,quint8 rotate=0);
    ~Tetromino();
    void setTetro(Tetromino &tetro);
    void rotate(quint8 n);
    void setType(Tetromino::Type type,quint8 rotate=-1);
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
    void setColor(Color::Type color);
    Block &blockAt(int index);
    QPoint pointAt(int index) const;
    QPoint size() const;
private:
    Type m_type;
    Color::Type m_color;
    Bl blocks[4];
    void setParentBlock();
    QPoint m_size;
};

#endif // TETROMINO_H
