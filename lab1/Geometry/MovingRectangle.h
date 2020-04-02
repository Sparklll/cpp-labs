#ifndef MOVINGRECTANGLE_H
#define MOVINGRECTANGLE_H

#include "Figure.h"
#include <QGraphicsObject>
#include <QPainter>
#include <QPropertyAnimation>

class MovingRectangle : public QGraphicsObject
{
public:
    MovingRectangle(QGraphicsItem *parent = 0);
    ~MovingRectangle();

public:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};

#endif // MOVINGRECTANGLE_H
