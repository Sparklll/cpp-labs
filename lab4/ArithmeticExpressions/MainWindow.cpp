#include "MainWindow.h"
#include "Stack.h"
#include "ui_MainWindow.h"
#include <QDebug>
#include <QMessageBox>
#include <QRegExpValidator>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setInputLimits();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setInputLimits()
{
    ui->aField->setValidator((new QRegExpValidator(*new QRegExp("[0-9]+\\.?[0-9]{2}"), this)));
    ui->bField->setValidator((new QRegExpValidator(*new QRegExp("[0-9]+\\.?[0-9]{2}"), this)));
    ui->cField->setValidator((new QRegExpValidator(*new QRegExp("[0-9]+\\.?[0-9]{2}"), this)));
    ui->dField->setValidator((new QRegExpValidator(*new QRegExp("[0-9]+\\.?[0-9]{2}"), this)));
    ui->eField->setValidator((new QRegExpValidator(*new QRegExp("[0-9]+\\.?[0-9]{2}"), this)));
}

bool MainWindow::checkIfFillInAllInputFields()
{
    if (!ui->aField->text().isEmpty() && !ui->bField->text().isEmpty()
        && !ui->cField->text().isEmpty() && !ui->dField->text().isEmpty()
        && !ui->eField->text().isEmpty() && !ui->mathExprField->text().isEmpty()) {
        return true;
    }
    return false;
}

void MainWindow::on_calcButton_clicked()
{
    if (checkIfFillInAllInputFields()) {
        QString expression = ui->mathExprField->text();
        ui->resultField->setText(
            QString::number(calculatePostfixExpression(infixToPostfix(expression))));
    } else {
        QMessageBox::information(this, "Arithmetic Expressions", "Please, fill in all variables!");
    }
}

int MainWindow::operatorPrecedence(QChar c)
{
    if (c == '*' || c == '/')
        return 2;
    else if (c == '+' || c == '-')
        return 1;
    else
        return -1;
}

QString MainWindow::infixToPostfix(QString infixExpression)
{
    Stack<QChar> stack;
    QString result;
    for (int i = 0; i < infixExpression.length(); i++) {
        if (infixExpression[i] == ' ') {
            continue;
        } else if (QRegExp("[a-zA-Z]").exactMatch(QString(QChar(infixExpression[i])))) {
            result += infixExpression[i];
        }

        else if (infixExpression[i] == '(') {
            stack.push('(');
        }

        else if (infixExpression[i] == ')') {
            while (!stack.empty() && stack.top() != '(') {
                QChar c = stack.top();
                result += c;
                stack.pop();
            }
            if (stack.top() == '(') {
                stack.pop();
            }
        }

        else {
            while (!stack.empty()
                   && operatorPrecedence(infixExpression.at(i)) <= operatorPrecedence(stack.top())) {
                QChar c = stack.top();
                result += c;
                stack.pop();
            }
            stack.push(infixExpression.at(i));
        }
    }

    while (!stack.empty()) {
        QChar c = stack.top();
        result += c;
        stack.pop();
    }

    return result.toLower();
}

bool MainWindow::isMathOperator(QChar c)
{
    QString mathOperators = "+-*/";

    return mathOperators.contains(c) ? true : false;
}

qreal MainWindow::calculateMathExpression(qreal operand1, qreal operand2, QChar mathOperator)
{
    switch (mathOperator.unicode()) {
    case '+': {
        return operand1 + operand2;
        break;
    }
    case '-': {
        return operand1 - operand2;
        break;
    }
    case '*': {
        return operand1 * operand2;
        break;
    }
    case '/': {
        return operand1 / operand2;
        break;
    }
    default: {
        return 0;
    }
    }
}

QString MainWindow::replaceVariablesWithFieldValues(QChar c)
{
    switch (c.unicode()) {
    case 'a':
        return ui->aField->text();

    case 'b':
        return ui->bField->text();

    case 'c':
        return ui->cField->text();

    case 'd':
        return ui->dField->text();

    case 'e':
        return ui->eField->text();

    default:
        return "0";
    }
}

qreal MainWindow::calculatePostfixExpression(QString postfixExpression)
{
    Stack<QString> stack;

    for (int i = 0; i < postfixExpression.length(); i++) {
        if (isMathOperator(postfixExpression[i])) {
            qreal operand2 = stack.top().toDouble();
            stack.pop();
            qreal operand1 = stack.top().toDouble();
            stack.pop();

            stack.push(
                QString::number(calculateMathExpression(operand1, operand2, postfixExpression[i])));

        } else {
            // In our case we should replace a,b,c,d with their values from fields
            stack.push(replaceVariablesWithFieldValues(postfixExpression[i]));
        }
    }
    return stack.top().toDouble();
}

void MainWindow::on_clearFieldsButton_clicked()
{
    ui->aField->clear();
    ui->bField->clear();
    ui->cField->clear();
    ui->dField->clear();
    ui->eField->clear();
    ui->mathExprField->clear();
    ui->resultField->clear();
}
