#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "Figure.h"
class Rectangle : public Figure
{
private:
public:
    Rectangle(QPointF point, QGraphicsItem *parent = 0);

    qreal getWidth() const;
    qreal getHeight() const;
    QPointF topLeftCorner() const;

    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    virtual QRectF boundingRect() const;
    virtual qreal getFigureArea() const;
    virtual qreal getFigurePerimeter() const;
};

#endif // RECTANGLE_H
