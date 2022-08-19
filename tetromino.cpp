#include "tetromino.h"

namespace Tetrominos
{
static constexpr QPoint Tetro[][4]=
{
    {QPoint(0,0),QPoint(0,1),QPoint(0,2),QPoint(0,3)}, // i
    {QPoint(0,0),QPoint(1,0),QPoint(1,1),QPoint(1,2)}, // j
    {QPoint(0,0),QPoint(0,1),QPoint(0,2),QPoint(1,0)}, // l
    {QPoint(0,0),QPoint(0,1),QPoint(1,0),QPoint(1,1)}, // o
    {QPoint(0,1),QPoint(0,2),QPoint(1,0),QPoint(1,1)}, // s
    {QPoint(0,0),QPoint(0,1),QPoint(0,2),QPoint(1,1)}, // t
    {QPoint(0,0),QPoint(0,1),QPoint(1,1),QPoint(1,2)}  // z
};
}

Tetromino::Tetromino()
{
    setParentBlock();
    setType(Tetromino::NONE);
}

Tetromino::Tetromino(Tetromino::Type type, quint8 rotate)
{
    setParentBlock();
    setType(type,rotate);
}

Tetromino::~Tetromino()
{

}

void Tetromino::setTetro(Tetromino &tetro)
{
    this->m_size=tetro.m_size;
    this->m_type=tetro.m_type;
    this->m_color=tetro.m_color;
    for(int i=0;i<4;i++)
    {
        this->blocks[i].setBl(tetro.blocks[i]);
        this->blocks[i].setPos(blocks[i].XY::xy()*20);
    }

}

void Tetromino::rotate(quint8 n)
{
    n%=4;
    if(n<=0)
    {
        if(n==0)
        {
            for(int i=0;i<4;i++)
            {
                QPoint t=blocks[i].XY::xy();
                blocks[i].XY::setXY(t.y(),m_size.x()-t.x()-1);
                blocks[i].setPos(blocks[i].XY::xy()*20);
            }
            qSwap(m_size.rx(),m_size.ry());
        }
    }
    else
    {
        for(int i=0;i<=n;i++)
        {
            rotate(0);
        }
    }
}

void Tetromino::setType(Tetromino::Type type, quint8 rotate)
{
    if(type==Tetromino::NONE)
    {
        m_size=QPoint(0,0);
    }
    else
    {
        int max_x=0,max_y=0;
        for(int i=0;i<4;i++)
        {
            QPoint curXY=Tetrominos::Tetro[type][i];
            max_x=qMax(max_x,curXY.x());
            max_y=qMax(max_y,curXY.y());
            blocks[i].setXY(curXY);
            blocks[i].setPos(blocks[i].XY::xy()*20);
        }
        m_size.setX(max_x+1);
        m_size.setY(max_y+1);
        this->rotate(rotate);
    }
    m_type=type;
    setColor(Color::Type(type));
}

QRectF Tetromino::boundingRect() const
{
    return QRectF(QPointF(0,0),m_size*20);
}

void Tetromino::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
//    QRectF rec=boundingRect();
//    painter->drawRect(rec);
}

void Tetromino::setColor(Color::Type color)
{
    for(int i=0;i<4;i++)
    {
        blocks[i].setColor(color);
    }
}

Block &Tetromino::blockAt(int index)
{
    return blocks[index];
}

QPoint Tetromino::pointAt(int index) const
{
    return blocks[index].xy();
}

QPoint Tetromino::size() const
{
    return m_size;
}

void Tetromino::setParentBlock()
{
    for(int i=0;i<4;i++)
    {
        blocks[i].setParentItem(this);
    }
}
