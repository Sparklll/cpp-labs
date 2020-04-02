#include "MainWindow.h"
#include "Figure.h"
#include "Scene.h"
#include "Ship.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->graphicsView,
            SIGNAL(capturedFigureChanged()),
            this,
            SLOT(toShowCapturedFigureData()));

    scene = new Scene(QRectF(-100, -100, 800, 800), this);
    ui->graphicsView->setScene(scene);

    pen = new QPen(Qt::cyan, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
    brush = new QBrush(QColor(0, 0, 0, 0));
    ui->penColorPanel->setPalette(QPalette(Qt::cyan));

    // ADDING SHIP TO THE SCENE
    //Ship *ship = new Ship(QPoint(0, 0));
    //scene->addItem(ship);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_penSizeSlider_valueChanged(int value)
{
    pen->setWidth(value);
    ui->penSizeLine->setText(QString::number(value));
    if (isItemCapturedOnView()) {
        ui->graphicsView->getCapturedFigure()->getFigurePen()->setWidth(value);
        scene->update();
    }
}

void MainWindow::on_gridCheckBox_stateChanged(int arg1)
{
    ui->graphicsView->setGridVisible(!ui->graphicsView->isGridVisible());
    scene->update();
}

void MainWindow::on_pointCheckBox_stateChanged(int arg1)
{
    ui->graphicsView->setPointVisible(!ui->graphicsView->isPointVisible());
    scene->update();
}

void MainWindow::on_penColorButton_clicked()
{
    QColor color = QColorDialog::getColor();
    if (color.isValid()) {
        pen->setColor(color);
        ui->penColorPanel->setPalette(QPalette(color));
        if (isItemCapturedOnView()) {
            ui->graphicsView->getCapturedFigure()->getFigurePen()->setColor(color);
            scene->update();
        }
    }
}

void MainWindow::on_brushColorButton_clicked()
{
    QColor color = QColorDialog::getColor();
    if (color.isValid()) {
        brush->setColor(color);
        ui->brushColorPanel->setPalette(QPalette(color));
        if (isItemCapturedOnView()) {
            ui->graphicsView->getCapturedFigure()->getFigureBrush()->setColor(color);
            scene->update();
        }
    }
}

void MainWindow::on_resetPainterButton_clicked()
{
    pen->setColor(Qt::cyan);
    pen->setWidth(1);
    brush->setStyle(Qt::NoBrush);
    ui->penColorPanel->setPalette(QPalette(Qt::cyan));
    ui->brushColorPanel->setPalette(QPalette());
    if (isItemCapturedOnView()) {
        ui->graphicsView->getCapturedFigure()->getFigurePen()->setColor(Qt::cyan);
        ui->graphicsView->getCapturedFigure()->getFigurePen()->setWidth(1);
        ui->graphicsView->getCapturedFigure()->getFigureBrush()->setStyle(Qt::NoBrush);
        scene->update();
    }
}

void MainWindow::on_penColorButton_pressed()
{
    ui->penColorButton->setIconSize(QSize(20, 20));
}

void MainWindow::on_penColorButton_released()
{
    ui->penColorButton->setIconSize(QSize(30, 30));
}

void MainWindow::on_brushColorButton_pressed()
{
    ui->brushColorButton->setIconSize(QSize(20, 20));
}

void MainWindow::on_brushColorButton_released()
{
    ui->brushColorButton->setIconSize(QSize(30, 30));
}

void MainWindow::on_resetPainterButton_pressed()
{
    ui->resetPainterButton->setIconSize(QSize(20, 20));
}

void MainWindow::on_resetPainterButton_released()
{
    ui->resetPainterButton->setIconSize(QSize(30, 30));
}

bool MainWindow::isItemCapturedOnView()
{
    if (ui->graphicsView->getCapturedFigure() != nullptr
        && ui->graphicsView->getCapturedFigure()->isCaptured()) {
        return true;
    } else {
        return false;
    }
}
void MainWindow::toShowCapturedFigureData()
{
    ui->areaLine->setText(QString::number(ui->graphicsView->getCapturedFigure()->getFigureArea()));
    ui->perimeterLine->setText(
        QString::number(ui->graphicsView->getCapturedFigure()->getFigurePerimeter()));
}

void MainWindow::on_clearSceneButton_clicked()
{
    scene->clear();
}

void MainWindow::on_rectangleButton_clicked()
{
    scene->setItemSelectedToDraw(true);
    scene->setFigureType(Scene::Rectangle);
}

void MainWindow::on_ellipseButton_clicked()
{
    scene->setItemSelectedToDraw(true);
    scene->setFigureType(Scene::Ellipse);
}

void MainWindow::on_triangleButton_clicked()
{
    scene->setItemSelectedToDraw(true);
    scene->setFigureType(Scene::Triangle);
}

void MainWindow::on_squareButton_clicked()
{
    scene->setItemSelectedToDraw(true);
    scene->setFigureType(Scene::Square);
}

void MainWindow::on_circleButton_clicked()
{
    scene->setItemSelectedToDraw(true);
    scene->setFigureType(Scene::Circle);
}

void MainWindow::on_polygonButton_clicked()
{
    scene->setItemSelectedToDraw(true);
    scene->setFigureType(Scene::Polygon);
}
