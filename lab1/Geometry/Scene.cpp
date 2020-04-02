#include "Scene.h"

int Scene::getTypeFigure() const
{
    return typeFigure;
}

void Scene::setFigureType(int value)
{
    typeFigure = value;
}

bool Scene::isItemSelectedToDraw() const
{
    return itemSelectedToDraw;
}

void Scene::setItemSelectedToDraw(bool value)
{
    itemSelectedToDraw = value;
}

Figure *Scene::getFigure() const
{
    return figure;
}

void Scene::setFigure(Figure *value)
{
    figure = value;
}

Scene::Scene(QObject *parent)
    : QGraphicsScene(parent), itemSelectedToDraw(false), typeFigure(-1), figure(nullptr)
{}

Scene::Scene(const QRectF &sceneRect, QObject *parent)
    : QGraphicsScene(sceneRect, parent), itemSelectedToDraw(false), typeFigure(-1), figure(nullptr)
{}

Scene::Scene(qreal x, qreal y, qreal width, qreal height, QObject *parent)
    : QGraphicsScene(x, y, width, height, parent), itemSelectedToDraw(false), typeFigure(-1),
      figure(nullptr)
{}
