#include "MovingRectangle.h"

MovingRectangle::MovingRectangle(QGraphicsItem *parent) : QGraphicsObject(parent)
{
    this->setPos(50, 500);
    QPropertyAnimation *animation = new QPropertyAnimation(this, "pos");
    animation->setDuration(8000);
    animation->setEasingCurve(QEasingCurve::SineCurve);
    animation->setEndValue(QPoint(scenePos().x() + 500, scenePos().y()));
    animation->setLoopCount(-1);
    animation->start();
}

MovingRectangle::~MovingRectangle() {}

QRectF MovingRectangle::boundingRect() const
{
    return QRectF(-100, -30, 200, 60);
}

void MovingRectangle::paint(QPainter *painter,
                            const QStyleOptionGraphicsItem *option,
                            QWidget *widget)
{
    painter->setPen(QPen(Qt::cyan, 5, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    painter->setBrush(Qt::blue);
    painter->drawRect(-100, -30, 200, 60);
}
