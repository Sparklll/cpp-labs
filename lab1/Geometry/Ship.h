#ifndef SHIP_H
#define SHIP_H

#include <MovingRectangle.h>
#include <QGraphicsObject>
#include <QPropertyAnimation>

class Ship : public MovingRectangle
{
public:
    Ship(QPoint point, QGraphicsItem *parent = 0);

    virtual qreal getFigureArea() const;
    virtual qreal getFigurePerimeter() const;
};

class Ramp : public QGraphicsObject
{
public:
    Ramp(QGraphicsObject *parent = 0);

    virtual QRectF boundingRect() const;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};

class Flagpole : public QGraphicsObject
{
public:
    Flagpole(QGraphicsObject *parent = 0);

    virtual QRectF boundingRect() const;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};

class Flag : public QGraphicsObject
{
public:
    Flag(QGraphicsObject *parent = 0);

    virtual QRectF boundingRect() const;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};

class Mast : public QGraphicsObject
{
public:
    Mast(QGraphicsObject *parent = 0);

    virtual QRectF boundingRect() const;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};

#endif // SHIP_H
