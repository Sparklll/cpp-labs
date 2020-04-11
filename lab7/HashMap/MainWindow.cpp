#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <QDebug>
#include <QMessageBox>
#include <QRegExpValidator>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), hashMap(new HashMap<QString, QString>(32))
{
    ui->setupUi(this);

    qsrand(time(0));
    ui->numberOfElementsField->setValidator(new QRegExpValidator(*new QRegExp("[1-9][0-9]+"), this));
}

MainWindow::~MainWindow()
{
    delete ui;
}

QString MainWindow::generatePassword(int passwordLength)
{
    QString passwordAlphabet
        = "|my!;Q_^]@:tjUgZEI/hlOrJFq(#ep{fCcx~+iPvAD=.Vn,<SbNo'RHw>K$s`LBMGuY)W*[-kza%}dT&X?~";
    int alphabetLength = passwordAlphabet.length();

    QString result;

    for (int i = 0; i < passwordLength; i++) {
        result.append(passwordAlphabet.at(qrand() % alphabetLength));
    }
    return result;
}

// Hash function for HashMap<QString, QString> case
template<>
int HashMap<QString, QString>::hashFunction(QString key)
{
    // It is "djb2". Very simple, fast and efficient string hashing function
    unsigned long long hash = 5381;
    int c;

    for (int i = 0; i < key.length(); i++) {
        c = key.at(i).unicode();
        hash = ((hash << 5) + hash) + c;
    }

    return hash % getArraySize();
}

void MainWindow::updateHashMapView()
{
    ui->hashMapView->clear();

    for (int i = 0; i < hashMap->getArraySize(); i++) {
        QString hashMapLine = QString::number(i) + "  : ";
        HashNode<QString, QString> *current = hashMap->getHashArray()[i]->getHead();

        while (current != nullptr) {
            hashMapLine.append(current->getKey() + " ==> ");
            current = current->next;
        }
        ui->hashMapView->insertPlainText(hashMapLine + "\n");
    }
}

void MainWindow::on_fillHashMapButton_clicked()
{
    // Filling the HashMap with keys which represented as random passwords(8 characters max)
    // (value fields are not used for simplicity, they are empty strings),
    // ==> represents a pointer to the next element,
    // as an example, HashMap size selected (32)
    if (!ui->numberOfElementsField->text().isEmpty()) {
        int numberOfElements = ui->numberOfElementsField->text().toInt();
        hashMap = new HashMap<QString, QString>(32);
        for (int i = 0; i < numberOfElements; i++) {
            HashNode<QString, QString> *newNode
                = new HashNode<QString, QString>(generatePassword(rand() % 8 + 1), "");
            hashMap->insertNode(newNode);
        }
        updateHashMapView();
        ui->numberOfElementsField->clear();
    } else {
        QMessageBox::warning(this, "HashMap", "Fill in \"HashMap size\" Field!");
    }
}
void MainWindow::on_insertElementButton_clicked()
{
    if (!ui->insertElementKeyField->text().isEmpty()) {
        QString key = ui->insertElementKeyField->text();
        hashMap->insertNode(new HashNode<QString, QString>(key, ""));
        updateHashMapView();
        ui->insertElementKeyField->clear();
    } else {
        QMessageBox::warning(this, "HashMap", "Fill in \"Key\" Field!");
    }
}
void MainWindow::on_deleteElementButton_clicked()
{
    if (!ui->deleteElementKeyField->text().isEmpty()) {
        QString key = ui->deleteElementKeyField->text();
        hashMap->deleteNode(key);
        updateHashMapView();
        ui->deleteElementKeyField->clear();
    } else {
        QMessageBox::warning(this, "HashMap", "Fill in \"Key\" Field!");
    }
}
void MainWindow::on_findElementButton_clicked()
{
    if (!ui->findElementKeyField->text().isEmpty()) {
        ui->outputBox->clear();
        QString key = ui->findElementKeyField->text();
        HashNode<QString, QString> *foundNode = hashMap->find(key);
        if (foundNode != nullptr) {
            ui->outputBox->insertPlainText(
                "Key : " + foundNode->getKey() + ", Value : "
                + foundNode
                      ->getValue()); // (value fields are not used for simplicity, they are empty strings)
            updateHashMapView();
        }
        ui->findElementKeyField->clear();
    } else {
        QMessageBox::warning(this, "HashMap", "Fill in \"Key\" Field!");
    }
}

// Hash function for HashMap<int, QString> case, i.e task case
template<>
int HashMap<int, QString>::hashFunction(int key)
{
    //Knuth's multiplicative method of hash for integers
    unsigned long long hash = key * 2654435761 >> 32;
    return hash % getArraySize();
}

void MainWindow::on_solveTaskButton_clicked()
{
    ui->outputBox->clear();
    HashMap<int, QString> *taskHashMap = new HashMap<int, QString>(32);

    // Filling the HashMap with random number (in range 1-100) of random int keys(in range 1-10000)
    // (value fields are not used for simplicity, they are empty strings),
    // ==> represents a pointer to the next element,
    // as an example, HashMap size selected (32)
    int numberOfElements = qrand() % 100 + 1;
    int sumOfKeys = 0;
    for (int i = 0; i < numberOfElements; i++) {
        int key = qrand() % 10000 + 1;
        sumOfKeys += key;
        taskHashMap->insertNode(new HashNode<int, QString>(key, ""));
    }

    int averageKeyValue = sumOfKeys / numberOfElements;
    int numOfElemsWithKeyMoreThanAverage = 0;

    // Hashmap output
    for (int i = 0; i < taskHashMap->getArraySize(); i++) {
        QString hashMapLine = QString::number(i) + "  : ";
        HashNode<int, QString> *current = taskHashMap->getHashArray()[i]->getHead();

        while (current != nullptr) {
            if (current->getKey() > averageKeyValue) {
                numOfElemsWithKeyMoreThanAverage++;
            }
            hashMapLine.append(QString::number(current->getKey()) + " ==> ");
            current = current->next;
        }
        ui->outputBox->insertPlainText(hashMapLine + "\n");
    }

    ui->outputBox->insertPlainText("Average key value : " + QString::number(averageKeyValue) + "\n");
    ui->outputBox->insertPlainText("Answer : " + QString::number(numOfElemsWithKeyMoreThanAverage)
                                   + "\n");
}
