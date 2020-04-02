#include "Square.h"

Square::Square(QPointF point, QGraphicsItem *parent) : Figure(point, parent) {}

void Square::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setPen(*getFigurePen());
    painter->setBrush(*getFigureBrush());

    if (isCaptured()) {
        painter->setBrush(QColor(118, 39, 171, 255));
    }

    QRectF square(-100, -100, 200, 200);
    painter->drawPolygon(square);
}

QRectF Square::boundingRect() const
{
    return QRectF(-100, -100, 200, 200);
}

qreal Square::getFigureArea() const
{
    return (int) (200 * 200 * getFigureScale());
}

qreal Square::getFigurePerimeter() const
{
    return (int) (200 * 4 * getFigureScale());
}
