#ifndef CIRCLE_H
#define CIRCLE_H

#include "Figure.h"
#include <QtMath>
class Circle : public Figure
{
public:
    Circle(QPointF point, QGraphicsItem *parent = 0);

    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    virtual QRectF boundingRect() const;
    virtual qreal getFigureArea() const;
    virtual qreal getFigurePerimeter() const;
};

#endif // CIRCLE_H
