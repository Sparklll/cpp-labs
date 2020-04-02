#ifndef POLYGON_H
#define POLYGON_H

#include "Figure.h"
#include <QtMath>
class Polygon : public Figure
{
public:
    Polygon(QPointF point, QGraphicsItem *parent = 0);

    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    virtual QRectF boundingRect() const;
    virtual qreal getFigureArea() const;
    virtual qreal getFigurePerimeter() const;
};

#endif // POLYGON_H
