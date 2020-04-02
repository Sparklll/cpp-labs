#include "Dot.h"

Dot::Dot(QGraphicsItem *parent) : QGraphicsItem(parent) {}

Dot::~Dot() {}

QRectF Dot::boundingRect() const
{
    return QRectF(-5, -5, 10, 10);
}

void Dot::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setPen(Qt::cyan);
    painter->setBrush(QColor(84, 118, 204, 255));
    painter->drawEllipse(-5, -5, 10, 10);
}
