#ifndef VIEW_H
#define VIEW_H

#include <QDebug>
#include <QGraphicsItem>
#include <QGraphicsItemGroup>
#include <QGraphicsView>
#include <QKeyEvent>
#include <QMouseEvent>
#include <QPainter>
#include <QPropertyAnimation>
#include <QTimeLine>
#include <QtMath>

#include "Circle.h"
#include "Dot.h"
#include "Figure.h"
#include "Oval.h"
#include "Polygon.h"
#include "Rectangle.h"
#include "Scene.h"
#include "Square.h"
#include "Triangle.h"

class View : public QGraphicsView
{
    Q_OBJECT

private:
    static int zValue;
    int gridSize;
    bool gridVisible;
    bool pointVisible;
    bool itemPressed;
    QColor gridColor;
    QPointF *capturedPoint;
    Figure *capturedFigure;
    QGraphicsItem *dot;
    Scene *customScene;

    QPen *pen;
    QBrush *brush;
    QPainter *painter;

    qreal calculateRadius();
    qreal currentRotationAngle();

public:
    View(QGraphicsScene *scene, QWidget *parent = nullptr);
    View(QWidget *parent = nullptr);

    bool isGridVisible() const;
    void setGridVisible(bool value);

    bool isItemPressed() const;
    void setItemPressed(bool value);

    bool isPointVisible() const;
    void setPointVisible(bool value);

    Figure *getCapturedFigure() const;

signals:
    void capturedFigureChanged();

protected:
    virtual void drawBackground(QPainter *painter, const QRectF &rect);
    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseReleaseEvent(QMouseEvent *event);
    virtual void mouseMoveEvent(QMouseEvent *event);
    virtual void wheelEvent(QWheelEvent *event);
    virtual void keyPressEvent(QKeyEvent *event);
    virtual void resizeEvent(QResizeEvent *event);
};

#endif // VIEW_H
