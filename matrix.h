#ifndef MATRIX_H
#define MATRIX_H

#include <QGraphicsItem>
#include <QPainter>
#include <QRectF>
#include "block.h"
#include "tetromino.h"

class Matrix : public QGraphicsItem
{
public:
    Matrix();
    ~Matrix();
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;

// Matrix
public:
    void setupMatrix(int col,int row);
    void setupMatrix(QPoint size);
//    void setEmptyAt(int i,int j,bool empty=true);
private:
    Block **matrix;

//    int *bPRow;

    QPointF m_padding;

    bool isSetup;
    void newMatrix(int col,int row);
    void deleteMatrix();
public:
    Block &blockAt(int x,int y);
    Block &blockAt(QPoint xy);
    QPoint xy();

private:
    int m_row,m_col;

    void setParentItems();
    void setPosItems();
};

#endif // MATRIX_H
