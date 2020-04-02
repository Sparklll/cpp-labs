#include "Ship.h"

Ship::Ship(QPoint point, QGraphicsItem *parent) : MovingRectangle(parent)
{
    QGraphicsObject *shipRamp = new Ramp(this);
    QGraphicsObject *shipFlagpole = new Flagpole(this);
    QGraphicsObject *flag = new Flag(this);
    QGraphicsObject *mast = new Mast(this);
}

qreal Ship::getFigureArea() const {}

qreal Ship::getFigurePerimeter() const {}

Ramp::Ramp(QGraphicsObject *parent) : QGraphicsObject(parent) {}

QRectF Ramp::boundingRect() const {}

void Ramp::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setPen(QPen(Qt::cyan, 5, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    painter->setBrush(Qt::blue);

    QPolygon leftRamp;
    leftRamp << QPoint(-100, -30);
    leftRamp << QPoint(-100, 30);
    leftRamp << QPoint(-150, -30);

    QPolygon rightRamp;
    rightRamp << QPoint(100, -30);
    rightRamp << QPoint(100, 30);
    rightRamp << QPoint(150, -30);

    painter->drawPolygon(leftRamp);
    painter->drawPolygon(rightRamp);
}

Flagpole::Flagpole(QGraphicsObject *parent) : QGraphicsObject(parent) {}

QRectF Flagpole::boundingRect() const {}

void Flagpole::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setPen(QPen(Qt::black, 5, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    painter->drawLine(-150, -35, -150, -300);
}

Flag::Flag(QGraphicsObject *parent) : QGraphicsObject(parent)
{
    QPropertyAnimation *flagAnimation = new QPropertyAnimation(this, "pos");
    flagAnimation->setDuration(10000);
    flagAnimation->setEasingCurve(QEasingCurve::SineCurve);
    flagAnimation->setEndValue(QPoint(0, 170));
    flagAnimation->setLoopCount(-1);
    flagAnimation->start();
}

QRectF Flag::boundingRect() const {}

void Flag::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setPen(QPen(Qt::green, 5, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    painter->setBrush(Qt::white);

    QPolygon flag;
    flag << QPoint(-150, -300);
    flag << QPoint(-100, -270);
    flag << QPoint(-150, -240);
    painter->drawPolygon(flag);
}

Mast::Mast(QGraphicsObject *parent) : QGraphicsObject(parent) {}

QRectF Mast::boundingRect() const {}

void Mast::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setPen(QPen(Qt::black, 5, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    painter->drawLine(-0, -35, 0, -200);

    painter->setPen(QPen(Qt::red, 5, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    painter->setBrush(Qt::white);

    QPolygon mast;
    mast << QPoint(0, -220);
    mast << QPoint(-120, -70);
    mast << QPoint(120, -70);
    painter->drawPolygon(mast);
}
