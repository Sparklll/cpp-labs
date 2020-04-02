#include "Circle.h"

Circle::Circle(QPointF point, QGraphicsItem *parent) : Figure(point, parent) {}

void Circle::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setPen(*getFigurePen());
    painter->setBrush(*getFigureBrush());

    if (isCaptured()) {
        painter->setBrush(QColor(118, 39, 171, 255));
    }

    painter->drawEllipse(QRectF(-80, -80, 160, 160));
}

QRectF Circle::boundingRect() const
{
    return QRectF(-80, -80, 160, 160);
}

qreal Circle::getFigureArea() const
{
    return (int) (getFigureScale() * M_PI * qPow(80, 2));
}

qreal Circle::getFigurePerimeter() const
{
    return (int) (getFigureScale() * 2 * M_PI * 80);
}
