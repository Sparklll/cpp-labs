#ifndef SQUARE_H
#define SQUARE_H

#include "Figure.h"
class Square : public Figure
{
public:
    Square(QPointF point, QGraphicsItem *parent = 0);

    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    virtual QRectF boundingRect() const;
    virtual qreal getFigureArea() const;
    virtual qreal getFigurePerimeter() const;
};

#endif // SQUARE_H
