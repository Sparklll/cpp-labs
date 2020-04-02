#include "View.h"

int View::zValue = 0;

bool View::isItemPressed() const
{
    return itemPressed;
}

void View::setItemPressed(bool value)
{
    itemPressed = value;
}

bool View::isPointVisible() const
{
    return pointVisible;
}

void View::setPointVisible(bool value)
{
    pointVisible = value;
    dot->setVisible(pointVisible);
}

Figure *View::getCapturedFigure() const
{
    return capturedFigure;
}

qreal View::calculateRadius()
{
    qreal dx = capturedFigure->x() - capturedPoint->x();
    qreal dy = capturedFigure->y() - capturedPoint->y();
    qreal radius = sqrt(qPow(dx, 2) + qPow(dy, 2));
    return radius;
}

qreal View::currentRotationAngle()
{
    return qAtan2(capturedPoint->y() - capturedFigure->y(),
                  capturedFigure->x() - capturedPoint->x());
}

View::View(QGraphicsScene *scene, QWidget *parent)
    : QGraphicsView(scene, parent), gridSize(20), gridColor(QColor(159, 99, 212, 100)),
      gridVisible(true), pointVisible(false), capturedFigure(nullptr),
      capturedPoint(new QPointF(0, 0)), itemPressed(false), customScene(nullptr), dot(new Dot())
{
    dot->setPos(-10, -10);
    setRenderHint(QPainter::Antialiasing);
    setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
}

View::View(QWidget *parent)
    : QGraphicsView(parent), gridSize(20), gridColor(QColor(159, 99, 212, 100)), gridVisible(true),
      pointVisible(false), capturedFigure(nullptr), capturedPoint(new QPointF(0, 0)),
      itemPressed(false), customScene(nullptr), dot(new Dot())
{
    dot->setPos(-10, -10);
    setRenderHint(QPainter::Antialiasing);
    setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
}

bool View::isGridVisible() const
{
    return gridVisible;
}

void View::setGridVisible(bool value)
{
    gridVisible = value;
}

void View::drawBackground(QPainter *painter, const QRectF &rect)
{
    if (isGridVisible()) {
        painter->setPen(gridColor);
        QRect r = rect.toRect();
        int xmin = r.left() - r.left() % gridSize - gridSize;
        int ymin = r.top() - r.top() % gridSize - gridSize;
        int xmax = r.right() - r.right() % gridSize + gridSize;
        int ymax = r.bottom() - r.bottom() % gridSize + gridSize;
        for (int x = xmin; x <= xmax; x += gridSize) {
            painter->drawLine(x, r.top(), x, r.bottom());
        }
        for (int y = ymin; y <= ymax; y += gridSize) {
            painter->drawLine(r.left(), y, r.right(), y);
        }
    }
}

void View::mousePressEvent(QMouseEvent *event)
{
    if (customScene == nullptr) {
        customScene = (Scene *) scene();
    }
    if (!customScene->isItemSelectedToDraw()) {
        QGraphicsItem *item = itemAt(event->pos());
        if (item != nullptr && event->button() == Qt::LeftButton) {
            setItemPressed(true);
            this->setCursor(QCursor(Qt::ClosedHandCursor));

            if (item == capturedFigure) {
                capturedFigure->setCaptured(!capturedFigure->isCaptured());
                scene()->update();
            } else {
                if (capturedFigure != nullptr) {
                    capturedFigure->setCaptured(false);
                }
                capturedFigure = (Figure *) item;
                capturedFigure->setCaptured(true);
                capturedFigure->setZValue(++zValue);
                scene()->update();
                emit capturedFigureChanged();
            }

        } else if (item == nullptr && event->button() == Qt::LeftButton) {
            if (!scene()->items().contains(dot)) {
                dot = new Dot();
                scene()->addItem(dot);
                if (!isPointVisible()) {
                    dot->setVisible(false);
                }
            }
            dot->setPos(mapToScene(event->pos().x(), event->pos().y()));
            capturedPoint->setX(dot->x());
            capturedPoint->setY(dot->y());
            scene()->update();

        } else if (item == nullptr && event->button() == Qt::RightButton) {
            if (capturedFigure != nullptr) {
                capturedFigure->setCaptured(false);
            }
            customScene->setItemSelectedToDraw(false);

            scene()->update();
        }
    } else {
        switch (customScene->getTypeFigure()) {
        case Scene::Rectangle: {
            Rectangle *item = new Rectangle(mapToScene(event->pos()));
            item->setPos(mapToScene(event->pos()));
            customScene->setFigure(item);
            break;
        }
        case Scene::Square: {
            Square *item = new Square(event->pos());
            item->setPos(mapToScene(event->pos()));
            customScene->setFigure(item);
            break;
        }

        case Scene::Ellipse: {
            Oval *item = new Oval(event->pos());
            item->setPos(mapToScene(event->pos()));
            customScene->setFigure(item);
            break;
        }
        case Scene::Circle: {
            Circle *item = new Circle(event->pos());
            item->setPos(mapToScene(event->pos()));
            customScene->setFigure(item);
            break;
        }
        case Scene::Polygon: {
            Polygon *item = new Polygon(event->pos());
            item->setPos(mapToScene(event->pos()));
            customScene->setFigure(item);
            break;
        }
        case Scene::Triangle: {
            Triangle *item = new Triangle(event->pos());
            item->setPos(mapToScene(event->pos()));
            customScene->setFigure(item);
            break;
        }
        }

        customScene->addItem(customScene->getFigure());
        scene()->update();
    }
}

void View::mouseReleaseEvent(QMouseEvent *event)
{
    setItemPressed(false);
    this->setCursor(QCursor(Qt::ArrowCursor));
    if (customScene->isItemSelectedToDraw()) {
        customScene->setItemSelectedToDraw(false);
    }
}

void View::mouseMoveEvent(QMouseEvent *event)
{
    if (!customScene->isItemSelectedToDraw()) {
        QGraphicsView::mouseMoveEvent(event);
        if (isItemPressed()) {
            capturedFigure->setPos(mapToScene(event->pos()));
            scene()->update();
        }
    } else {
        customScene->getFigure()->setEndPoint(mapToScene(event->pos()));
        scene()->update();
    }
}

void View::wheelEvent(QWheelEvent *event)
{
    if (capturedFigure != nullptr && capturedFigure->isCaptured()) {
        QPropertyAnimation *animation = new QPropertyAnimation(capturedFigure, "scale");
        animation->setDuration(500);

        int degrees = event->delta() / 8;
        if (degrees > 0) {
            capturedFigure->setFigureScale(capturedFigure->getFigureScale() + 0.1);
        } else {
            if (capturedFigure->getFigureScale() > 0.2) {
                capturedFigure->setFigureScale(capturedFigure->getFigureScale() - 0.1);
            }
        }
        animation->setEndValue(capturedFigure->getFigureScale());
        animation->start();
        scene()->update();
        emit capturedFigureChanged();
    }
}

void View::keyPressEvent(QKeyEvent *event)
{
    if (capturedFigure != nullptr && capturedFigure->isCaptured()) {
        int key = event->nativeScanCode();
        if (key == 113) {
            capturedFigure->setFigureRotation(capturedFigure->getFigureRotation() - 1);
            capturedFigure->setRotation(capturedFigure->getFigureRotation());
            scene()->update();
        } else if (key == 114) {
            capturedFigure->setFigureRotation(capturedFigure->getFigureRotation() + 1);
            capturedFigure->setRotation(capturedFigure->getFigureRotation());
            scene()->update();
        } else if (key == 119) {
            scene()->removeItem(capturedFigure);
            capturedFigure = nullptr;
            scene()->update();
        } else if (key == 38 || key == 40) {
            qreal angle = key == 38 ? 0.05 : -0.05;
            qreal radius = calculateRadius();
            qreal x = capturedPoint->x() + radius * qCos(currentRotationAngle() + angle);
            qreal y = capturedPoint->y() - radius * qSin(currentRotationAngle() + angle);

            //scene()->addEllipse(x, y, 5, 5);
            capturedFigure->setPos(x, y);
            scene()->update();
        }
    }
}

void View::resizeEvent(QResizeEvent *event)
{
    fitInView(scene()->sceneRect(), Qt::KeepAspectRatio);
}
