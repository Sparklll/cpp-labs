#include "Rectangle.h"

Rectangle::Rectangle(QPointF point, QGraphicsItem *parent) : Figure(point, parent) {}

qreal Rectangle::getWidth() const
{
    return qAbs(getEndPoint().x() - getStartPoint().x());
}

qreal Rectangle::getHeight() const
{
    qAbs(getEndPoint().y() - getStartPoint().y());
}

void Rectangle::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setPen(*getFigurePen());
    painter->setBrush(*getFigureBrush());

    if (isCaptured()) {
        painter->setBrush(QColor(118, 39, 171, 255));
    }

    QRectF rect(-getWidth() / 2, -getHeight() / 2, getWidth(), getHeight());

    painter->drawRect(rect);
}

QRectF Rectangle::boundingRect() const
{
    return QRectF(-getWidth() / 2, -getHeight() / 2, getWidth(), getHeight());
}

qreal Rectangle::getFigureArea() const
{
    return (int) (getWidth() * getHeight() * getFigureScale());
}

qreal Rectangle::getFigurePerimeter() const
{
    return (int) ((getWidth() + getHeight()) * 2 * getFigureScale());
}
