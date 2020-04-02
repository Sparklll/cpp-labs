#ifndef FIGURE_H
#define FIGURE_H

#include <QCursor>
#include <QDebug>
#include <QGradient>
#include <QGraphicsObject>
#include <QKeyEvent>
#include <QMouseEvent>
#include <QPainter>

class Figure : public QGraphicsObject
{
    Q_OBJECT
public:
    Figure(QPointF point, QGraphicsItem *parent = 0);
    ~Figure();
    virtual QRectF boundingRect() const = 0;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
        = 0;

    qreal getFigureScale() const;
    void setFigureScale(const qreal &value);

    bool isCaptured() const;
    void setCaptured(bool value);

    qreal getFigureRotation() const;
    void setFigureRotation(const qreal &value);

    QPen *getFigurePen() const;
    QBrush *getFigureBrush() const;

    virtual qreal getFigureArea() const = 0;
    virtual qreal getFigurePerimeter() const = 0;

    QPointF getStartPoint() const;
    QPointF getEndPoint() const;

    void setStartPoint(const QPointF &value);
    void setEndPoint(const QPointF &value);

private:
    QPen *figurePen;
    QBrush *figureBrush;
    bool captured = false;

    qreal figureScale;
    qreal figureRotation;

    QPointF startPoint;
    QPointF endPoint;
};

#endif // FIGURE_H
