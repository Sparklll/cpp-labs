#ifndef SCENE_H
#define SCENE_H

#include <Figure.h>
#include <QDebug>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QGraphicsSceneEvent>
#include <QPainter>

class Scene : public QGraphicsScene
{
    Q_OBJECT

private:
    int typeFigure;
    bool itemSelectedToDraw;
    Figure *figure;

public:
    Scene(QObject *parent);

    Scene(const QRectF &sceneRect, QObject *parent);

    Scene(qreal x, qreal y, qreal width, qreal height, QObject *parent);

    enum FigureTypes {
        Rectangle,
        Square,
        Ellipse,
        Circle,
        Polygon,
        Triangle,
    };
    int getTypeFigure() const;
    void setFigureType(int value);

    bool isItemSelectedToDraw() const;
    void setItemSelectedToDraw(bool value);

    Figure *getFigure() const;
    void setFigure(Figure *value);
};

#endif // SCENE_H
