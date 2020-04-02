#include "Oval.h"

Oval::Oval(QPointF point, QGraphicsItem *parent) : Figure(point, parent) {}

qreal Oval::getWidth() const
{
    return qAbs(getEndPoint().x() - getStartPoint().x());
}

qreal Oval::getHeight() const
{
    qAbs(getEndPoint().y() - getStartPoint().y());
}

QPointF Oval::topLeftCorner() const
{
    return QPointF(getEndPoint().x() > getStartPoint().x() ? getStartPoint().x() : getEndPoint().x(),
                   getEndPoint().y() > getStartPoint().y() ? getStartPoint().y()
                                                           : getEndPoint().y());
}

void Oval::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setPen(*getFigurePen());
    painter->setBrush(*getFigureBrush());

    if (isCaptured()) {
        painter->setBrush(QColor(118, 39, 171, 255));
    }

    QRectF rect(-getWidth() / 2, -getHeight() / 2, getWidth(), getHeight());

    painter->drawEllipse(rect);
}

QRectF Oval::boundingRect() const
{
    return QRectF(-getWidth() / 2, -getHeight() / 2, getWidth(), getHeight());
}

qreal Oval::getFigureArea() const
{
    return (int) (M_PI * getWidth() * getHeight() * getFigureScale() / 4);
}

qreal Oval::getFigurePerimeter() const
{
    return (int) (2 * M_PI * sqrt(qPow(getWidth() / 2, 2) + qPow(getHeight() / 2, 2))
                  * getFigureScale());
}
