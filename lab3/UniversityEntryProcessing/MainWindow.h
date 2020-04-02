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

#include "Enrollee.h"

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
    void on_saveButton_clicked();
    void on_saveAsButton_clicked();
    void on_addButton_clicked();
    void on_editButton_clicked();
    void on_saveChangesButton_clicked();
    void on_deleteButton_clicked();
    void on_searchButton_clicked();
    void on_tableWidget_cellDoubleClicked(int row, int column);

    void on_resetButton_clicked();

    void on_acceptFiltersButton_clicked();

    void on_currentPassingScoreBox_valueChanged(int arg1);

private:
    Ui::MainWindow *ui;
    QFile databaseOpenFile;
    QFile databaseSaveFile;
    QJsonDocument localJsonBase;
    QVector<Enrollee> enrolleeVector;

    enum class DocOptions { ADD, DELETE, EDIT };
    enum class SortOption { TOTAL_SCORE, SC, CT1, CT2, CT3, NAME, SURNAME, DEFAULT };

    void setInputLimits();
    void clearInputFields();
    void setWidgetHeader();
    bool checkIfFillInAllInputFields();
    void uiSwitcherWhileEditing(bool selector);
    void clearTableSelection();
    void insertObjectIntoWidget(Enrollee enrollee);
    void updateBase(QJsonObject enrolleeObject, DocOptions option);
    void updateTableWidget();
    bool containsAllSearchedWords(QVector<QString> searchedWords, QString diskToString);
    bool elementVisibleInWidget(int totalScore);
    static bool caseInsensitiveSortingByName(const Enrollee &enrollee1, const Enrollee &enrollee2);
    static bool caseInsensitiveSortingBySurname(const Enrollee &enrollee1,
                                                const Enrollee &enrollee2);
    static bool sortingByTotalScore(const Enrollee &enrollee1, const Enrollee &enrollee2);
    static bool sortingBySC(const Enrollee &enrollee1, const Enrollee &enrollee2);
    static bool sortingByCT1(const Enrollee &enrollee1, const Enrollee &enrollee2);
    static bool sortingByCT2(const Enrollee &enrollee1, const Enrollee &enrollee2);
    static bool sortingByCT3(const Enrollee &enrollee1, const Enrollee &enrollee2);
    QVector<Enrollee> sortEnrolleeVector(SortOption option);
};
#endif // MAINWINDOW_H
