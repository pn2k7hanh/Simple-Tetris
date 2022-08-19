#include "block.h"

Block::Block()
{
    setEmpty(true);
    setColor(Color::red);
}

Block::Block(Color::Type color,bool empty)
{
    setEmpty(empty);
    setColor(color);
}


Block::~Block()
{

}

QRectF Block::boundingRect() const
{
    return QRectF(0,0,20,20);
}

void Block::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    if(!isEmpty())
    {
        QRectF temp=boundingRect();
        QRectF rec(temp.topLeft()+QPointF(1,1),temp.bottomRight()-QPointF(1,1));
        painter->setPen(Qt::transparent);
        painter->fillRect(rec,m_color);
        painter->drawRect(rec);
    }
}

QBrush Block::color() const
{
    return m_color;
}

void Block::setColor(Color::Type color,bool empty)
{
    m_color=Color::Color[color];
    setEmpty(empty);
}


bool Block::isEmpty() const
{
    return Empty;
}

void Block::setEmpty(bool empty)
{
    Empty=empty;
}

Block &Block::setBlock(Block &block)
{
    this->m_color=block.m_color;
    this->Empty=block.Empty;
    return *this;
}
