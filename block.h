#ifndef BLOCK_H
#define BLOCK_H

#include <QGraphicsItem>
#include <QPainter>
#include <QPixmap>
#include <QBrush>
#include "color.h"

class Block : public QGraphicsItem
{
public:
    Block();
    Block(Color::Type color,bool empty=false);
    ~Block();
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
    QBrush color() const;
    void setColor(Color::Type color,bool empty=false);
    bool isEmpty() const;

    void setEmpty(bool empty);
    Block &setBlock(Block &block);
private:
    bool Empty;
    QBrush m_color;
};
#endif // BLOCK_H
