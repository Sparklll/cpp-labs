#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDateTime>
#include <QDebug>
#include <QFileDialog>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QMainWindow>
#include <QMessageBox>
#include <QTreeWidgetItem>
#include <QUuid>

#include "Disk.h"

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
    void on_openButton_clicked();
    void on_addButton_clicked();
    void on_saveButton_clicked();
    void on_searchButton_clicked();
    void on_tableWidget_cellDoubleClicked(int row, int column);
    void on_editButton_clicked();
    void on_saveChangesButton_clicked();
    void on_deleteButton_clicked();

    void on_saveAsButton_clicked();
    void on_applyFilters_clicked();
    void on_resetButton_clicked();

private:
    Ui::MainWindow *ui;
    QFile databaseOpenFile;
    QFile databaseSaveFile;
    QVector<Disk> diskVector;
    QJsonDocument localJsonBase;
    enum class DocOptions { ADD, DELETE, EDIT };
    enum class SortOption { NAME, AUTHOR, PRICE, DEFAULT };

    void setInputLimits();
    void clearInputFields();
    void setWidgetHeader();
    void updateBase(QJsonObject diskObject, DocOptions option);
    void insertDiskIntoWidget(Disk disk);
    void clearTableSelection();
    void uiSwitcherWhileEditing(bool selector);
    void updateTableWidget();
    bool checkIfFillInAllInputFields();
    bool elementVisibleInWidget(QString diskType);
    bool containsAllSearchedWords(QVector<QString> searchedWords, QString diskToString);
    QString makeDoubleTextLineCorrect(QString text);
    QVector<Disk> sortDiskVector(SortOption option);
};
#endif // MAINWINDOW_H
