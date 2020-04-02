#include "Polygon.h"

Polygon::Polygon(QPointF point, QGraphicsItem *parent) : Figure(point, parent) {}

void Polygon::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setPen(*getFigurePen());
    painter->setBrush(*getFigureBrush());

    if (isCaptured()) {
        painter->setBrush(QColor(118, 39, 171, 255));
    }

    QPolygonF hexagon;
}

QRectF Polygon::boundingRect() const {}

qreal Polygon::getFigureArea() const
{
    return 0;
}

qreal Polygon::getFigurePerimeter() const
{
    return 0;
}
