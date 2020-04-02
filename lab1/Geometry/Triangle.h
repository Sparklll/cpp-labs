#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "Figure.h"
#include <QtMath>
class Triangle : public Figure
{
public:
    Triangle(QPointF point, QGraphicsItem *parent = 0);

    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    virtual QRectF boundingRect() const;
    virtual qreal getFigureArea() const;
    virtual qreal getFigurePerimeter() const;
};

#endif // TRIANGLE_H
