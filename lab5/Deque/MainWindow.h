#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "Deque.h"
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    static int membersCount;
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void updateListOfMember();

private slots:
    void on_addFrontButton_clicked();
    void on_removeFrontButton_clicked();
    void on_addRearButton_clicked();
    void on_removeRearButton_clicked();
    void on_createTaskDequeButton_clicked();
    void on_resetDequesAndListButton_clicked();
    void on_solveTaskButton_clicked();

private:
    Ui::MainWindow *ui;
    Deque<QString> *deque;
    Deque<int> *taskDeque;
};
#endif // MAINWINDOW_H
