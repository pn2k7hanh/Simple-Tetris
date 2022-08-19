#include "matrix.h"

Matrix::Matrix()
{
    m_row=m_col=0;
    isSetup=false;
    m_padding=QPointF(20,20);
}

Matrix::~Matrix()
{
//    if(!isSetup) return;
//    for(int i=0;i<m_col;i++)
//    {
//        delete [] matrix[i];
//    }
//    delete []matrix;
////    delete []bPRow;
    deleteMatrix();
}

QRectF Matrix::boundingRect() const
{
//    return QRectF(m_padding*-1,QPoint(m_col,m_row)*20+m_padding);
    return QRectF(QPoint(0,0),QPoint(m_col,m_row)*20);
}

void Matrix::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
//    QRectF outsideBorder=boundingRect();
//    QRectF insideBorder=QRectF(QPointF(0,0),
//                               QPointF(m_col*20,m_row*20));
//    QRectF topleft(outsideBorder.topLeft(),insideBorder.bottomLeft());
//    QRectF bottomright(insideBorder.topRight(),outsideBorder.bottomRight());
//    QRectF topright(topleft.topRight(),bottomright.topRight());
//    QRectF bottomleft(topleft.bottomLeft(),bottomright.bottomLeft());
//    QPen pen(Qt::black);
//    QBrush brush(Qt::green);
//    painter->setPen(pen);
////    painter->setBrush(brush);

//    painter->fillRect(topleft,brush);
//    painter->fillRect(topright,brush);
//    painter->fillRect(bottomleft,brush);
//    painter->fillRect(bottomright,brush);
//    painter->drawRect(outsideBorder);
//    painter->drawRect(insideBorder);

}

void Matrix::setupMatrix(int col, int row)
{
    deleteMatrix();
    newMatrix(col,row);
    setParentItems();
    setPosItems();
}

void Matrix::setupMatrix(QPoint size)
{
    setupMatrix(size.x(),size.y());
}

//void Matrix::setEmptyAt(int i, int j, bool empty)
//{
//    if(empty!=matrix[i][j].isEmpty())
//    {
//        matrix[i][j].setEmpty(empty);
//        if(empty) bPRow[j]--;
//        else bPRow[j]++;
//    }
//}

void Matrix::newMatrix(int col, int row)
{
    if(isSetup) return;
    matrix=new Block*[col];
//    bPRow=new int[row];
//    for(int i=0;i<row;i++)
//    {
//        bPRow[i]=0;
//    }
    for(int i=0;i<col;i++)
    {
        matrix[i]=new Block[row];
        for(int j=0;j<row;j++)
        {
            matrix[i][j].setEmpty(true);
        }
    }
    m_row=row;
    m_col=col;
    isSetup=true;
}

void Matrix::deleteMatrix()
{
    if(!isSetup) return;
    for(int i=0;i<m_col;i++)
    {
        delete [] matrix[i];
    }
    delete []matrix;
//    delete []bPRow;
    m_col=m_row=0;
    isSetup=false;
}

QPoint Matrix::xy()
{
    return QPoint(this->x(),this->y());
}

Block &Matrix::blockAt(int x, int y)
{
    return matrix[x][y];
}

Block &Matrix::blockAt(QPoint xy)
{
    return blockAt(xy.x(),xy.y());
}

void Matrix::setParentItems()
{
    if(isSetup)
    {
        for(int i=0;i<10;i++)
        {
            for(int j=0;j<20;j++)
            {
                matrix[i][j].setParentItem(this);
            }
        }
    }
}

void Matrix::setPosItems()
{
    if(isSetup)
    {
        for(int i=0;i<10;i++)
        {
            for(int j=0;j<20;j++)
            {
                matrix[i][j].setPos(QPointF(i,j)*20);
            }
        }
    }
}
