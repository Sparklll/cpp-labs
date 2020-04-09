#include <QMessageBox>
#include <QString>

#include "MainWindow.h"
#include "Tree.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), binarySearchTree(Tree<int, QString>())
{
    ui->setupUi(this);

    // Set up widgets
    ui->itemsTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->itemsTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->treeView->setSelectionMode(QAbstractItemView::NoSelection);
    ui->itemsTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->itemsTable->setSelectionMode(QAbstractItemView::NoSelection);
    ui->itemsTable->setFocusPolicy(Qt::NoFocus);
    ui->invNumberField->setValidator(new QRegExpValidator(*new QRegExp("[1-9][0-9]+"), this));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_fillTreeFromTableButton_clicked()
{
    if (binarySearchTree.getRoot() != nullptr) {
        binarySearchTree.deleteTree(binarySearchTree.getRoot());
    }

    int rowCount = ui->itemsTable->rowCount();
    for (int i = 0; i < rowCount; i++) {
        QString itemName = ui->itemsTable->item(i, 0)->text();
        int invItemNumber = ui->itemsTable->item(i, 1)->text().toInt();

        binarySearchTree.insertNode(invItemNumber, itemName);
    }

    updateTreeView();
}

void MainWindow::on_balanceTreeButton_clicked()
{
    binarySearchTree.balanceTree();
    updateTreeView();
}

void MainWindow::on_findByKeyButton_clicked()
{
    if (!ui->findByKeyField->text().isEmpty()) {
        ui->outputBox->clear();
        int key = ui->findByKeyField->text().toInt();
        Node<int, QString> *foundNode = binarySearchTree.findNode(key);
        if (foundNode != nullptr) {
            QString output = "Key : " + QString::number(foundNode->key)
                             + ", Data : " + foundNode->data + ".";
            ui->outputBox->appendPlainText(output);
        }
        ui->findByKeyField->clear();
    } else {
        QMessageBox::warning(this, "Binary Search Tree", "Fill in \"Key\" Field!");
    }
}

void MainWindow::on_deleteByKeyButton_clicked()
{
    if (!ui->deleteByKeyField->text().isEmpty()) {
        int key = ui->deleteByKeyField->text().toInt();
        binarySearchTree.deleteNode(key);

        ui->deleteByKeyField->clear();
        updateTreeView();
    } else {
        QMessageBox::warning(this, "Binary Search Tree", "Fill in \"Key\" Field!");
    }
}

void MainWindow::preOrderTraversalOutput(Node<int, QString> *localRoot)
{
    if (localRoot != nullptr) {
        QString output = "Key : " + QString::number(localRoot->key) + ", Data : " + localRoot->data
                         + ".";

        ui->outputBox->appendPlainText(output);
        preOrderTraversalOutput(localRoot->leftChild);
        preOrderTraversalOutput(localRoot->rightChild);
    }
}

void MainWindow::inOrderTraversalOutput(Node<int, QString> *localRoot)
{
    if (localRoot != nullptr) {
        QString output = "Key : " + QString::number(localRoot->key) + ", Data : " + localRoot->data
                         + ".";

        inOrderTraversalOutput(localRoot->leftChild);
        ui->outputBox->appendPlainText(output);
        inOrderTraversalOutput(localRoot->rightChild);
    }
}

void MainWindow::postOrderTraversalOutput(Node<int, QString> *localRoot)
{
    if (localRoot != nullptr) {
        QString output = "Key : " + QString::number(localRoot->key) + ", Data : " + localRoot->data
                         + ".";

        postOrderTraversalOutput(localRoot->leftChild);
        postOrderTraversalOutput(localRoot->rightChild);
        ui->outputBox->appendPlainText(output);
    }
}

void MainWindow::on_printTreeButton_clicked()
{
    ui->outputBox->clear();

    if (ui->preOrderRadioButton->isChecked()) {
        preOrderTraversalOutput(binarySearchTree.getRoot());
    } else if (ui->inOrderRadioButton->isChecked()) {
        inOrderTraversalOutput(binarySearchTree.getRoot());
    } else if (ui->postOrderRadioButton->isChecked()) {
        postOrderTraversalOutput(binarySearchTree.getRoot());
    }
}

void MainWindow::on_addItemButton_clicked()
{
    if ((!ui->itemNameField->text().isEmpty() && !ui->invNumberField->text().isEmpty())
        && (ui->toTreeCheckbox->isChecked() || ui->toTableCheckbox->isChecked())) {
        QString itemName = ui->itemNameField->text();
        QString itemInvNumber = ui->invNumberField->text();

        if (ui->toTableCheckbox->isChecked()) {
            ui->itemsTable->insertRow(ui->itemsTable->rowCount());
            int currentRow = ui->itemsTable->rowCount() - 1;
            ui->itemsTable->setItem(currentRow, 0, new QTableWidgetItem(itemName));
            ui->itemsTable->setItem(currentRow, 1, new QTableWidgetItem(itemInvNumber));
        }

        if (ui->toTreeCheckbox->isChecked()) {
            binarySearchTree.insertNode(itemInvNumber.toInt(), itemName);
        }

        ui->itemNameField->clear();
        ui->invNumberField->clear();
        updateTreeView();

    } else {
        QMessageBox::warning(this, "Binary Search Tree", "Fill in all fields!");
    }
}

void MainWindow::fillTreeView(QTreeWidgetItem *parentItem, Node<int, QString> *node)
{
    if (node != nullptr) {
        QTreeWidgetItem *item = new QTreeWidgetItem();
        QString itemText = "Key(" + QString::number(node->key) + "), " + "Data(" + node->data + ")";
        item->setText(0, itemText);
        if (parentItem == nullptr) {
            ui->treeView->addTopLevelItem(item);
        } else {
            parentItem->addChild(item);
        }
        item->setExpanded(true);
        fillTreeView(item, node->leftChild);
        fillTreeView(item, node->rightChild);
    }
}

void MainWindow::updateTreeView()
{
    ui->treeView->clear();

    if (binarySearchTree.getRoot() != nullptr) {
        fillTreeView(nullptr, binarySearchTree.getRoot());
    }
}

void MainWindow::on_clearTableButton_clicked()
{
    ui->itemsTable->setRowCount(0);
}

void MainWindow::on_clearTreeButton_clicked()
{
    binarySearchTree.deleteTree(binarySearchTree.getRoot());
    updateTreeView();
}

void MainWindow::on_solveTaskButton_clicked()
{
    Node<int, QString> *current = binarySearchTree.getRoot();
    Node<int, QString> *parent = binarySearchTree.getRoot();
    if (current != nullptr) {
        current = current->leftChild;
        if (current != nullptr) {
            if (current->rightChild != nullptr) {
                while (current->rightChild != nullptr) {
                    parent = current;
                    current = current->rightChild;
                }
                parent->rightChild = nullptr;
            } else {
                parent->leftChild = nullptr;
            }
            binarySearchTree.deleteTree(current);
        }
        updateTreeView();
    }
}
