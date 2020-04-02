#include "Figure.h"

Figure::Figure(QPointF point, QGraphicsItem *parent)
    : QGraphicsObject(parent), figureScale(1.0), figureRotation(0), captured(false),
      figurePen(new QPen(Qt::cyan, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin)),
      figureBrush(new QBrush(QColor(0, 0, 0, 0)))
{
    this->setStartPoint(mapFromScene(point));
    this->setEndPoint(mapFromScene(point));
}

Figure::~Figure() {}

qreal Figure::getFigureScale() const
{
    return figureScale;
}

bool Figure::isCaptured() const
{
    return captured;
}

void Figure::setCaptured(bool value)
{
    captured = value;
}

qreal Figure::getFigureRotation() const
{
    return figureRotation;
}

void Figure::setFigureRotation(const qreal &value)
{
    figureRotation = value;
}

QPen *Figure::getFigurePen() const
{
    return figurePen;
}

QBrush *Figure::getFigureBrush() const
{
    return figureBrush;
}

QPointF Figure::getStartPoint() const
{
    return startPoint;
}

void Figure::setStartPoint(const QPointF &value)
{
    startPoint = value;
}

void Figure::setEndPoint(const QPointF &value)
{
    endPoint = value;
}

QPointF Figure::getEndPoint() const
{
    return endPoint;
}

void Figure::setFigureScale(const qreal &value)
{
    figureScale = value;
}
