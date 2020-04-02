#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
      , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setInputLimits();
    setWidgetHeader();
    QJsonObject obj;
    QJsonObject obj2;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setInputLimits()
{
    ui->nameField->setValidator(new QRegExpValidator(*new QRegExp("[A-Za-zА-Яа-яёЁ]+"), this));
    ui->surnameField->setValidator(new QRegExpValidator(*new QRegExp("[A-Za-zА-Яа-яёЁ]+"), this));
    ui->patronymicField->setValidator(new QRegExpValidator(*new QRegExp("[A-Za-zА-Яа-яёЁ]+"), this));
}

bool MainWindow::checkIfFillInAllInputFields()
{
    if (!ui->nameField->text().isEmpty() && !ui->surnameField->text().isEmpty()
        && !ui->patronymicField->text().isEmpty() && !ui->adressField->toPlainText().isEmpty()) {
        return true;
    }
    return false;
}

void MainWindow::clearInputFields()
{
    ui->nameField->clear();
    ui->surnameField->clear();
    ui->patronymicField->clear();
    ui->adressField->clear();
    ui->scSpinBox->setValue(0);
    ui->ct1SpinBox->setValue(0);
    ui->ct2SpinBox->setValue(0);
    ui->ct3SpinBox->setValue(0);
}

void MainWindow::setWidgetHeader()
{
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->tableWidget->horizontalHeader()->setMinimumSectionSize(120);
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget->setFocusPolicy(Qt::NoFocus);
    ui->tableWidget->verticalHeader()->setHighlightSections(false);
    ui->tableWidget->horizontalHeader()->setHighlightSections(false);

    ui->tableWidget->setColumnCount(10);
    QStringList headerLabelsList = {"Id",
                                    "Name",
                                    "Surname",
                                    "Patronymic",
                                    "Adress",
                                    "Total Score",
                                    "SC",
                                    "CT №1",
                                    "CT №2",
                                    "CT №3"};
    ui->tableWidget->setHorizontalHeaderLabels(headerLabelsList);
    ui->tableWidget->horizontalHeader()->setStyleSheet("QHeaderView { font-size: 13pt; }");
    ui->tableWidget->setColumnHidden(0, true);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(5, QHeaderView::Stretch);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(6, QHeaderView::Stretch);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(7, QHeaderView::Stretch);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(8, QHeaderView::Stretch);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(9, QHeaderView::Stretch);
}

void MainWindow::uiSwitcherWhileEditing(bool selector)
{
    if (selector) {
        ui->tableWidget->setSelectionMode(QAbstractItemView::SelectionMode::SingleSelection);
        ui->tableWidget->setAttribute(Qt::WA_TransparentForMouseEvents, false);
    } else {
        ui->tableWidget->setSelectionMode(QAbstractItemView::SelectionMode::NoSelection);
        ui->tableWidget->setAttribute(Qt::WA_TransparentForMouseEvents, true);
    }

    ui->openButton->setEnabled(selector);
    ui->saveButton->setEnabled(selector);
    ui->addButton->setEnabled(selector);
    ui->editButton->setEnabled(selector);
    ui->saveChangesButton->setEnabled(!selector);
    ui->deleteButton->setEnabled(selector);
    ui->searchButton->setEnabled(selector);
    ui->currentPassingScoreBox->setEnabled(selector);
    ui->resetButton->setEnabled(selector);
    ui->acceptFiltersButton->setEnabled(selector);
    ui->currentPassingScoreBox->setEnabled(selector);
}

void MainWindow::updateTableWidget()
{
    ui->tableWidget->setRowCount(0);
    QVector<Enrollee> tempEnrolleeVector;
    if (ui->sortByComboBox->currentIndex() == 0) {
        tempEnrolleeVector = sortEnrolleeVector(SortOption::DEFAULT);
    } else if (ui->sortByComboBox->currentIndex() == 1) {
        tempEnrolleeVector = sortEnrolleeVector(SortOption::TOTAL_SCORE);
    } else if (ui->sortByComboBox->currentIndex() == 2) {
        tempEnrolleeVector = sortEnrolleeVector(SortOption::SC);
    } else if (ui->sortByComboBox->currentIndex() == 3) {
        tempEnrolleeVector = sortEnrolleeVector(SortOption::CT1);
    } else if (ui->sortByComboBox->currentIndex() == 4) {
        tempEnrolleeVector = sortEnrolleeVector(SortOption::CT2);
    } else if (ui->sortByComboBox->currentIndex() == 5) {
        tempEnrolleeVector = sortEnrolleeVector(SortOption::CT3);
    } else if (ui->sortByComboBox->currentIndex() == 6) {
        tempEnrolleeVector = sortEnrolleeVector(SortOption::NAME);
    } else if (ui->sortByComboBox->currentIndex() == 7) {
        tempEnrolleeVector = sortEnrolleeVector(SortOption::SURNAME);
    }

    foreach (Enrollee enrollee, tempEnrolleeVector) {
        if (elementVisibleInWidget(enrollee.getTotalScore().toInt())) {
            insertObjectIntoWidget(enrollee);
        }
    }
}

void MainWindow::updateBase(QJsonObject enrolleeJsonObject, MainWindow::DocOptions option)
{
    QJsonObject majorJsonObject;
    QJsonArray jsonArray = QJsonValue(localJsonBase.object().value("University Entry Processing"))
                               .toArray();

    switch (option) {
    case MainWindow::DocOptions::ADD: {
        jsonArray.append(enrolleeJsonObject);
        majorJsonObject["University Entry Processing"] = jsonArray;
        localJsonBase.setObject(majorJsonObject);
        enrolleeVector.push_back(Enrollee::fromJsonObject(enrolleeJsonObject));
        break;
    }
    case MainWindow::DocOptions::DELETE: {
        QJsonArray updatedJsonArray;
        for (int i = 0; i < jsonArray.size(); i++) {
            if (jsonArray.at(i).toObject().value("Id") != enrolleeJsonObject.value("Id")) {
                updatedJsonArray.append(jsonArray.at(i).toObject());
            }
        }
        majorJsonObject["University Entry Processing"] = updatedJsonArray;
        localJsonBase.setObject(majorJsonObject);

        int indexOfDiskObject = -1;
        for (int i = 0; i < enrolleeVector.size(); i++) {
            if (enrolleeVector.at(i).getId() == enrolleeJsonObject.value("Id").toString()) {
                indexOfDiskObject = i;
                break;
            }
        }
        enrolleeVector.removeAt(indexOfDiskObject);
        break;
    }
    case MainWindow::DocOptions::EDIT: {
        QJsonArray updatedJsonArray;
        for (int i = 0; i < jsonArray.size(); i++) {
            if (jsonArray.at(i).toObject().value("Id") == enrolleeJsonObject.value("Id")) {
                updatedJsonArray.append(enrolleeJsonObject);
            } else {
                updatedJsonArray.append(jsonArray.at(i).toObject());
            }
        }
        majorJsonObject["University Entry Processing"] = updatedJsonArray;
        localJsonBase.setObject(majorJsonObject);

        int indexOfDiskObject;
        for (int i = 0; i < enrolleeVector.size(); i++) {
            if (enrolleeVector.at(i).getId() == enrolleeJsonObject.value("Id").toString()) {
                indexOfDiskObject = i;
                break;
            }
        }

        enrolleeVector.replace(indexOfDiskObject, Enrollee::fromJsonObject(enrolleeJsonObject));
        break;
    }
    }

    updateTableWidget();
}

bool MainWindow::elementVisibleInWidget(int totalScore)
{
    if (totalScore >= ui->minScoreSpinBox->value()) {
        if (ui->sufficientScoreCheckBox->isChecked()
            && totalScore >= ui->currentPassingScoreBox->value()) {
            return true;
        } else if (ui->outsidersCheckBox->isChecked()
                   && totalScore < ui->currentPassingScoreBox->value()) {
            return true;
        }
    }
    return false;
}

void MainWindow::insertObjectIntoWidget(Enrollee enrollee)
{
    QString id = enrollee.getId();
    QString name = enrollee.getName();
    QString surname = enrollee.getSurname();
    QString patronymic = enrollee.getPatronymic();
    QString adress = enrollee.getAdress();
    QString totalScore = enrollee.getTotalScore();
    QString sc = enrollee.getScore().at(0);
    QString ct1 = enrollee.getScore().at(1);
    QString ct2 = enrollee.getScore().at(2);
    QString ct3 = enrollee.getScore().at(3);

    ui->tableWidget->insertRow(ui->tableWidget->rowCount());
    int currentRow = ui->tableWidget->rowCount() - 1;

    ui->tableWidget->setItem(currentRow, 0, new QTableWidgetItem(id));
    ui->tableWidget->setItem(currentRow, 1, new QTableWidgetItem(name));
    ui->tableWidget->setItem(currentRow, 2, new QTableWidgetItem(surname));
    ui->tableWidget->setItem(currentRow, 3, new QTableWidgetItem(patronymic));
    ui->tableWidget->setItem(currentRow, 4, new QTableWidgetItem(adress));
    ui->tableWidget->setItem(currentRow, 5, new QTableWidgetItem(totalScore));
    ui->tableWidget->setItem(currentRow, 6, new QTableWidgetItem(sc));
    ui->tableWidget->setItem(currentRow, 7, new QTableWidgetItem(ct1));
    ui->tableWidget->setItem(currentRow, 8, new QTableWidgetItem(ct2));
    ui->tableWidget->setItem(currentRow, 9, new QTableWidgetItem(ct3));

    QColor rowColor = totalScore.toInt() >= ui->currentPassingScoreBox->value()
                          ? QColor(122, 205, 122, 100)
                          : QColor(205, 122, 122, 150);
    for (int i = 0; i < 10; i++) {
        ui->tableWidget->item(currentRow, i)->setBackground(rowColor);
    }
}

bool MainWindow::caseInsensitiveSortingByName(const Enrollee &enrollee1, const Enrollee &enrollee2)
{
    return enrollee1.getName().toLower() < enrollee2.getName().toLower();
}
bool MainWindow::caseInsensitiveSortingBySurname(const Enrollee &enrollee1,
                                                 const Enrollee &enrollee2)
{
    return enrollee1.getSurname().toLower() < enrollee2.getSurname().toLower();
}
bool MainWindow::sortingByTotalScore(const Enrollee &enrollee1, const Enrollee &enrollee2)
{
    return enrollee1.getTotalScore().toInt() > enrollee2.getTotalScore().toInt();
}
bool MainWindow::sortingBySC(const Enrollee &enrollee1, const Enrollee &enrollee2)
{
    return enrollee1.getScore().at(0).toInt() > enrollee2.getScore().at(0).toInt();
}
bool MainWindow::sortingByCT1(const Enrollee &enrollee1, const Enrollee &enrollee2)
{
    return enrollee1.getScore().at(1).toInt() > enrollee2.getScore().at(1).toInt();
}
bool MainWindow::sortingByCT2(const Enrollee &enrollee1, const Enrollee &enrollee2)
{
    return enrollee1.getScore().at(2).toInt() > enrollee2.getScore().at(2).toInt();
}
bool MainWindow::sortingByCT3(const Enrollee &enrollee1, const Enrollee &enrollee2)
{
    return enrollee1.getScore().at(3).toInt() > enrollee2.getScore().at(3).toInt();
}

QVector<Enrollee> MainWindow::sortEnrolleeVector(MainWindow::SortOption option)
{
    QVector<Enrollee> tempEnrolleeVector = enrolleeVector;
    switch (option) {
    case MainWindow::SortOption::TOTAL_SCORE: {
        qSort(tempEnrolleeVector.begin(), tempEnrolleeVector.end(), sortingByTotalScore);
        break;
    }
    case MainWindow::SortOption::SC: {
        qSort(tempEnrolleeVector.begin(), tempEnrolleeVector.end(), sortingBySC);
        break;
    }
    case MainWindow::SortOption::CT1: {
        qSort(tempEnrolleeVector.begin(), tempEnrolleeVector.end(), sortingByCT1);
        break;
    }
    case MainWindow::SortOption::CT2: {
        qSort(tempEnrolleeVector.begin(), tempEnrolleeVector.end(), sortingByCT2);
        break;
    }
    case MainWindow::SortOption::CT3: {
        qSort(tempEnrolleeVector.begin(), tempEnrolleeVector.end(), sortingByCT3);
        break;
    }
    case MainWindow::SortOption::NAME: {
        qSort(tempEnrolleeVector.begin(), tempEnrolleeVector.end(), caseInsensitiveSortingByName);
        break;
    }
    case MainWindow::SortOption::SURNAME: {
        qSort(tempEnrolleeVector.begin(), tempEnrolleeVector.end(), caseInsensitiveSortingBySurname);
        break;
    }
    default: {
        break;
    }
    }

    return tempEnrolleeVector;
}

void MainWindow::on_openButton_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Choose Base", "/home", "(*.json)");

    if (!fileName.isEmpty()) {
        enrolleeVector.clear();
        databaseOpenFile.setFileName(fileName);
        databaseOpenFile.open(QIODevice::ReadOnly);
        localJsonBase = QJsonDocument::fromJson(databaseOpenFile.readAll());
        databaseOpenFile.close();
        QJsonArray jsonArray
            = QJsonValue(localJsonBase.object().value("University Entry Processing")).toArray();
        for (int i = 0; i < jsonArray.size(); i++) {
            enrolleeVector.push_back(Enrollee::fromJsonObject(jsonArray.at(i).toObject()));
        }
        updateTableWidget();
    }
}

void MainWindow::on_addButton_clicked()
{
    if (checkIfFillInAllInputFields()) {
        QString name = ui->nameField->text();
        QString surname = ui->surnameField->text();
        QString patronymic = ui->patronymicField->text();
        QString adress = ui->adressField->toPlainText();
        QString sc = QString::number(ui->scSpinBox->value());
        QString ct1 = QString::number(ui->ct1SpinBox->value());
        QString ct2 = QString::number(ui->ct2SpinBox->value());
        QString ct3 = QString::number(ui->ct3SpinBox->value());

        Enrollee enrollee(QUuid::createUuid().toString(QUuid::Id128),
                          name,
                          surname,
                          patronymic,
                          adress,
                          QVector<QString>() << sc << ct1 << ct2 << ct3);
        updateBase(enrollee.toJsonObject(), DocOptions::ADD);
        clearInputFields();

    } else {
        QMessageBox::warning(this, "University Entry Processing", "Please, fill in all fields!");
    }
}

bool MainWindow::containsAllSearchedWords(QVector<QString> searchedWords, QString enrolleeToString)
{
    foreach (QString singleWord, searchedWords) {
        QString pattern = "\\b" + singleWord + "\\b";
        if (!enrolleeToString.contains(QRegExp(pattern))) {
            return false;
        }
    }
    return true;
}

void MainWindow::on_searchButton_clicked()
{
    if (!ui->searchField->text().isEmpty()) {
        ui->tableWidget->setRowCount(0);
        QVector<QString> searchingWords
            = ui->searchField->text().toLower().split(QRegExp("\\W+")).toVector();
        foreach (Enrollee enrollee, enrolleeVector) {
            QString enrolleeData = enrollee.toString().toLower();
            if (containsAllSearchedWords(searchingWords, enrolleeData)) {
                insertObjectIntoWidget(enrollee);
            }
        }
        ui->searchField->clear();
    } else {
        QMessageBox::warning(this, "University Entry Processing", "Fill in the search field!");
    }
}

void MainWindow::clearTableSelection()
{
    ui->tableWidget->clearSelection();
}

void MainWindow::on_tableWidget_cellDoubleClicked(int row, int column)
{
    clearTableSelection();
}

void MainWindow::on_editButton_clicked()
{
    QItemSelectionModel *selectionModel = ui->tableWidget->selectionModel();
    QModelIndex modelIndex = selectionModel->currentIndex();

    if (selectionModel->hasSelection()) {
        ui->nameField->setText(
            ui->tableWidget->model()->index(modelIndex.row(), 1).data().toString());
        ui->surnameField->setText(
            ui->tableWidget->model()->index(modelIndex.row(), 2).data().toString());
        ui->patronymicField->setText(
            ui->tableWidget->model()->index(modelIndex.row(), 3).data().toString());
        ui->adressField->setPlainText(
            ui->tableWidget->model()->index(modelIndex.row(), 4).data().toString());
        ui->scSpinBox->setValue(ui->tableWidget->model()->index(modelIndex.row(), 6).data().toInt());
        ui->ct1SpinBox->setValue(
            ui->tableWidget->model()->index(modelIndex.row(), 7).data().toInt());
        ui->ct2SpinBox->setValue(
            ui->tableWidget->model()->index(modelIndex.row(), 8).data().toInt());
        ui->ct3SpinBox->setValue(
            ui->tableWidget->model()->index(modelIndex.row(), 9).data().toInt());

        uiSwitcherWhileEditing(false);
    } else {
        QMessageBox::warning(this, "University Entry Processing", "Please, select a row to edit!");
    }
}

void MainWindow::on_saveChangesButton_clicked()
{
    QItemSelectionModel *selectedModel = ui->tableWidget->selectionModel();
    QModelIndex modelIndex = selectedModel->currentIndex();

    if (checkIfFillInAllInputFields()) {
        QString id = ui->tableWidget->model()->index(modelIndex.row(), 0).data().toString();
        QString name = ui->nameField->text();
        QString surname = ui->surnameField->text();
        QString patronymic = ui->patronymicField->text();
        QString adress = ui->adressField->toPlainText();
        QString sc = QString::number(ui->scSpinBox->value());
        QString ct1 = QString::number(ui->ct1SpinBox->value());
        QString ct2 = QString::number(ui->ct2SpinBox->value());
        QString ct3 = QString::number(ui->ct3SpinBox->value());

        Enrollee enrollee(id,
                          name,
                          surname,
                          patronymic,
                          adress,
                          QVector<QString>() << sc << ct1 << ct2 << ct3);
        updateBase(enrollee.toJsonObject(), DocOptions::EDIT);
        uiSwitcherWhileEditing(true);
        clearInputFields();

    } else {
        QMessageBox::warning(this, "University Entry Processing", "Please, fill in all fields!");
    }
}

void MainWindow::on_deleteButton_clicked()
{
    QItemSelectionModel *selectionModel = ui->tableWidget->selectionModel();
    if (selectionModel->hasSelection()) {
        QModelIndex modelIndex = selectionModel->currentIndex();

        QString id = ui->tableWidget->model()->index(modelIndex.row(), 0).data().toString();
        QString name = ui->tableWidget->model()->index(modelIndex.row(), 1).data().toString();
        QString surname = ui->tableWidget->model()->index(modelIndex.row(), 2).data().toString();
        QString patronymic = ui->tableWidget->model()->index(modelIndex.row(), 3).data().toString();
        QString adress = ui->tableWidget->model()->index(modelIndex.row(), 4).data().toString();
        QString totalScore = ui->tableWidget->model()->index(modelIndex.row(), 5).data().toString();
        QString sc = ui->tableWidget->model()->index(modelIndex.row(), 6).data().toString();
        QString ct1 = ui->tableWidget->model()->index(modelIndex.row(), 7).data().toString();
        QString ct2 = ui->tableWidget->model()->index(modelIndex.row(), 8).data().toString();
        QString ct3 = ui->tableWidget->model()->index(modelIndex.row(), 9).data().toString();

        Enrollee enrollee(id,
                          name,
                          surname,
                          patronymic,
                          adress,
                          QVector<QString>() << sc << ct1 << ct2 << ct3);
        updateBase(enrollee.toJsonObject(), DocOptions::DELETE);
        clearTableSelection();
    } else {
        QMessageBox::warning(this, "University Entry Processing", "Please, select a row to delete!");
    }
}

void MainWindow::on_saveButton_clicked()
{
    if (databaseOpenFile.exists()) {
        databaseOpenFile.open(QIODevice::WriteOnly);
        databaseOpenFile.resize(0);
        databaseOpenFile.write(localJsonBase.toJson());
        databaseOpenFile.close();
        QMessageBox::information(this, "University Entry Processing", "Saved successfully!");
    } else {
        QString databaseName = "UE Processing DB ("
                               + QDateTime::currentDateTime().toString("dd.MM.yyyy") + ").json";
        QString fileName = QFileDialog::getSaveFileName(this,
                                                        "Save DataBase",
                                                        databaseName,
                                                        "*.json");
        if (!fileName.isEmpty()) {
            databaseOpenFile.setFileName(fileName);
            databaseSaveFile.setFileName(fileName);
            databaseSaveFile.open(QIODevice::WriteOnly);
            databaseSaveFile.resize(0);
            databaseSaveFile.write(localJsonBase.toJson());
            databaseSaveFile.close();
            QMessageBox::information(this, "University Entry Processing", "Saved successfully!");
        }
    }
}

void MainWindow::on_saveAsButton_clicked()
{
    QString databaseName = "UE Processing DB ("
                           + QDateTime::currentDateTime().toString("dd.MM.yyyy") + ").json";
    QString fileName = QFileDialog::getSaveFileName(this, "Save DataBase", databaseName, "*.json");
    if (!fileName.isEmpty()) {
        databaseSaveFile.setFileName(fileName);
        databaseSaveFile.open(QIODevice::WriteOnly);
        databaseSaveFile.resize(0);
        databaseSaveFile.write(localJsonBase.toJson());
        databaseSaveFile.close(); 
        QMessageBox::information(this, "University Entry Processing", "Saved successfully!");
    }
}

void MainWindow::on_resetButton_clicked()
{
    ui->sufficientScoreCheckBox->setChecked(true);
    ui->outsidersCheckBox->setChecked(true);
    ui->sortByComboBox->setCurrentIndex(0);
    ui->minScoreSpinBox->setValue(0);
    updateTableWidget();
}

void MainWindow::on_acceptFiltersButton_clicked()
{
    updateTableWidget();
}

void MainWindow::on_currentPassingScoreBox_valueChanged(int arg1)
{
    updateTableWidget();
}
