#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <Tree.h>
#include <QMainWindow>
#include <QTreeWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void preOrderTraversalOutput(Node<int, QString> *localRoot);
    void inOrderTraversalOutput(Node<int, QString> *localRoot);
    void postOrderTraversalOutput(Node<int, QString> *localRoot);
    void fillTreeView(QTreeWidgetItem *parentItem, Node<int, QString> *node);
    void updateTreeView();

private slots:
    void on_fillTreeFromTableButton_clicked();
    void on_balanceTreeButton_clicked();
    void on_findByKeyButton_clicked();
    void on_deleteByKeyButton_clicked();
    void on_printTreeButton_clicked();
    void on_solveTaskButton_clicked();
    void on_addItemButton_clicked();
    void on_clearTableButton_clicked();

    void on_clearTreeButton_clicked();

private:
    Ui::MainWindow *ui;
    Tree<int, QString> binarySearchTree;
};

#endif // MAINWINDOW_H
