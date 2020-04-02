#ifndef OVAL_H
#define OVAL_H

#include "Figure.h"
#include <QtMath>
class Oval : public Figure
{
public:
    Oval(QPointF point, QGraphicsItem *parent = 0);

    qreal getWidth() const;
    qreal getHeight() const;
    QPointF topLeftCorner() const;

    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    virtual QRectF boundingRect() const;
    virtual qreal getFigureArea() const;
    virtual qreal getFigurePerimeter() const;
};

#endif // OVAL_H
