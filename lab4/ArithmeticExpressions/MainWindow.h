#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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
    void on_calcButton_clicked();

    void on_clearFieldsButton_clicked();

private:
    Ui::MainWindow *ui;

    QString infixToPostfix(QString infixExpression);
    QString replaceVariablesWithFieldValues(QChar c);
    int operatorPrecedence(QChar c);
    qreal calculatePostfixExpression(QString postfixExpression);
    qreal calculateMathExpression(qreal operand2, qreal operand1, QChar mathOperator);
    void setInputLimits();
    bool checkIfFillInAllInputFields();
    bool isMathOperator(QChar c);
};
#endif // MAINWINDOW_H
