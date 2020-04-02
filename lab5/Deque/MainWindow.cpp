#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <QDebug>
#include <QTime>

int MainWindow::membersCount = 0;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), deque(new Deque<QString>()),
      taskDeque(new Deque<int>())
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateListOfMember()
{
    ui->listOfMembers->clear();
    for (int i = 0; i < deque->size(); i++) {
        ui->listOfMembers->addItem(deque->operator[](i));
    }
    ui->numberOfMembersLine->setText("Сurrent number of members : " + QString::number(membersCount));
}

void MainWindow::on_addFrontButton_clicked()
{
    deque->insertFront("Member #" + QString::number(membersCount));
    membersCount++;

    updateListOfMember();
}

void MainWindow::on_removeFrontButton_clicked()
{
    if (!deque->isEmpty()) {
        deque->deleteFront();
        membersCount--;

        updateListOfMember();
    }
}

void MainWindow::on_addRearButton_clicked()
{
    deque->insertRear("Member #" + QString::number(membersCount));
    membersCount++;

    updateListOfMember();
}

void MainWindow::on_removeRearButton_clicked()
{
    if (!deque->isEmpty()) {
        deque->deleteRear();
        membersCount--;

        updateListOfMember();
    }
}

void MainWindow::on_createTaskDequeButton_clicked()
{
    ui->listOfMembers->clear();
    taskDeque->erase();
    qsrand(QTime::currentTime().msec());

    // example value
    int numberOfMembers = 10;

    for (int i = 0; i < numberOfMembers; i++) {
        int number = qrand() % 1000 - 500;
        taskDeque->insertFront(number);
        ui->listOfMembers->addItem(QString::number(number));
    }
}

void MainWindow::on_resetDequesAndListButton_clicked()
{
    ui->listOfMembers->clear();
    ui->numberOfMembersLine->clear();
    deque->erase();
    taskDeque->erase();
}

void MainWindow::on_solveTaskButton_clicked()
{
    ui->listOfMembers->clear();
    int dequeStartSize = taskDeque->size();

    for (int i = 0; i < dequeStartSize; i++) {
        int value = taskDeque->getRear();
        taskDeque->deleteRear();
        if (value >= 0) {
            taskDeque->insertFront(value);
        }
    }

    // Show result in listOfMembers
    for (int i = 0; i < taskDeque->size(); i++) {
        ui->listOfMembers->addItem(QString::number(taskDeque->operator[](i)));
    }
}
