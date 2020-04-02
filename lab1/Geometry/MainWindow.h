#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "MovingRectangle.h"
#include "Scene.h"
#include <QGraphicsItem>
#include <QGraphicsItemGroup>
#include <QGraphicsScene>
#include <QMainWindow>
#include <QPainter>
#include <QtWidgets>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_penSizeSlider_valueChanged(int value);
    void on_gridCheckBox_stateChanged(int arg1);

    void on_pointCheckBox_stateChanged(int arg1);

    void on_penColorButton_clicked();

    void on_brushColorButton_clicked();

    void on_resetPainterButton_clicked();

    void on_penColorButton_pressed();

    void on_penColorButton_released();

    void on_brushColorButton_pressed();

    void on_brushColorButton_released();

    void on_resetPainterButton_pressed();

    void on_resetPainterButton_released();

    void on_rectangleButton_clicked();

    void toShowCapturedFigureData();

    void on_ellipseButton_clicked();

    void on_clearSceneButton_clicked();

    void on_triangleButton_clicked();

    void on_squareButton_clicked();

    void on_circleButton_clicked();

    void on_polygonButton_clicked();

private:
    Ui::MainWindow *ui;
    Scene *scene;

    QPen *pen;
    QBrush *brush;

    bool isItemCapturedOnView();
};
#endif // MAINWINDOW_H
