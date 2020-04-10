#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "HashMap.h"
#include <QMainWindow>
#include <QString>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    QString generateSimplePassword(int passwordLength);
    void updateHashMapView();

private slots:
    void on_fillHashMapButton_clicked();
    void on_insertElementButton_clicked();
    void on_deleteElementButton_clicked();
    void on_findElementButton_clicked();
    void on_solveTaskButton_clicked();

private:
    Ui::MainWindow *ui;
    HashMap<QString, QString> *hashMap;
};
#endif // MAINWINDOW_H
