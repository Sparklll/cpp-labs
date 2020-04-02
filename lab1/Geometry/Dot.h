#ifndef ELLIPSE_H
#define ELLIPSE_H

#include <QGraphicsItem>
#include <QPainter>

class Dot : public QGraphicsItem
{
public:
    Dot(QGraphicsItem *parent = 0);
    ~Dot();

public:
    virtual QRectF boundingRect() const;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};

#endif // ELLIPSE_H
