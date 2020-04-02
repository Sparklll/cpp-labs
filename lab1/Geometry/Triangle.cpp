#include "Triangle.h"

Triangle::Triangle(QPointF point, QGraphicsItem *parent) : Figure(point, parent) {}

void Triangle::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setPen(*getFigurePen());
    painter->setBrush(*getFigureBrush());

    if (isCaptured()) {
        painter->setBrush(QColor(118, 39, 171, 255));
    }

    QPolygonF triangle;

    triangle << QPointF(-90, 90) << QPointF(0, -90) << QPointF(90, 90);

    painter->drawPolygon(triangle);
}

QRectF Triangle::boundingRect() const
{
    return QRectF(-90, -90, 180, 180);
}

qreal Triangle::getFigureArea() const
{
    return (int) (180 * 180 * getFigureScale() / 2);
}

qreal Triangle::getFigurePerimeter() const
{
    return (int) (getFigureScale() * sqrt(qPow(180, 2) + qPow(90, 2)) * 3);
}
