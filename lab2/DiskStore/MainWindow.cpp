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
    ui->priceField->setValidator((new QRegExpValidator(*new QRegExp("[0-9]+\\.?[0-9]{2}"), this)));
}

bool MainWindow::checkIfFillInAllInputFields()
{
    if (ui->diskTypeComboBox->currentIndex() != 0 && !ui->authorField->text().isEmpty()
        && !ui->priceField->text().isEmpty() && !ui->nameField->text().isEmpty()) {
        return true;
    }
    return false;
}

bool MainWindow::elementVisibleInWidget(QString diskType)
{
    if (diskType == "Game" && ui->gameCheckBox->isChecked()) {
        return true;
    } else if (diskType == "Film" && ui->filmCheckBox->isChecked()) {
        return true;
    } else if (diskType == "Music" && ui->musicCheckBox->isChecked()) {
        return true;
    } else if (diskType == "Photo" && ui->photoCheckBox->isChecked()) {
        return true;
    } else if (diskType == "Soft" && ui->softCheckBox->isChecked()) {
        return true;
    } else if (diskType == "Utility" && ui->utilityCheckBox->isChecked()) {
        return true;
    }
    return false;
}

void MainWindow::clearInputFields()
{
    ui->diskTypeComboBox->setCurrentIndex(0);
    ui->nameField->clear();
    ui->authorField->clear();
    ui->noteField->clear();
    ui->priceField->clear();
}

void MainWindow::setWidgetHeader()
{
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableWidget->setFocusPolicy(Qt::NoFocus);
    ui->tableWidget->verticalHeader()->setHighlightSections(false);
    ui->tableWidget->horizontalHeader()->setHighlightSections(false);

    ui->tableWidget->setColumnCount(6);
    QStringList headerLabelsList = {"Id", "Disk Type", "Name", "Author", "Note", "Price"};
    ui->tableWidget->setHorizontalHeaderLabels(headerLabelsList);
    ui->tableWidget->setColumnHidden(0, true);
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

    ui->addButton->setEnabled(selector);
    ui->deleteButton->setEnabled(selector);
    ui->editButton->setEnabled(selector);
    // ui->tableWidget->setEnabled(selector);
    ui->saveChangesButton->setEnabled(!selector);
    ui->searchButton->setEnabled(selector);
    ui->saveButton->setEnabled(selector);
    ui->openButton->setEnabled(selector);

    ui->applyFilters->setEnabled(selector);
    ui->resetButton->setEnabled(selector);
}

void MainWindow::updateTableWidget()
{
    ui->tableWidget->setRowCount(0);
    QVector<Disk> tempDiskVector;
    if (ui->orderByComboBox->currentIndex() == 0) {
        tempDiskVector = sortDiskVector(SortOption::DEFAULT);
    } else if (ui->orderByComboBox->currentIndex() == 1) {
        tempDiskVector = sortDiskVector(SortOption::NAME);
    } else if (ui->orderByComboBox->currentIndex() == 2) {
        tempDiskVector = sortDiskVector(SortOption::AUTHOR);
    } else if (ui->orderByComboBox->currentIndex() == 3) {
        tempDiskVector = sortDiskVector(SortOption::PRICE);
    }

    foreach (Disk disk, tempDiskVector) {
        insertDiskIntoWidget(disk);
    }
}

void MainWindow::updateBase(QJsonObject diskObject, MainWindow::DocOptions option)
{
    QJsonObject majorJsonObject;
    QJsonArray jsonArray = QJsonValue(localJsonBase.object().value("DiskStore")).toArray();

    switch (option) {
    case MainWindow::DocOptions::ADD: {
        jsonArray.append(diskObject);
        majorJsonObject["DiskStore"] = jsonArray;
        localJsonBase.setObject(majorJsonObject);
        diskVector.push_back(Disk::fromJsonObject(diskObject));
        break;
    }
    case MainWindow::DocOptions::DELETE: {
        QJsonArray updatedJsonArray;
        for (int i = 0; i < jsonArray.size(); i++) {
            if (jsonArray.at(i).toObject().value("Id") != diskObject.value("Id")) {
                updatedJsonArray.append(jsonArray.at(i).toObject());
            }
        }
        majorJsonObject["DiskStore"] = updatedJsonArray;
        localJsonBase.setObject(majorJsonObject);

        int indexOfDiskObject = -1;
        for (int i = 0; i < diskVector.size(); i++) {
            if (diskVector.at(i).getId() == diskObject.value("Id").toString()) {
                indexOfDiskObject = i;
                break;
            }
        }
        diskVector.removeAt(indexOfDiskObject);
        break;
    }
    case MainWindow::DocOptions::EDIT: {
        QJsonArray updatedJsonArray;
        for (int i = 0; i < jsonArray.size(); i++) {
            if (jsonArray.at(i).toObject().value("Id") == diskObject.value("Id")) {
                updatedJsonArray.append(diskObject);
            } else {
                updatedJsonArray.append(jsonArray.at(i).toObject());
            }
        }
        majorJsonObject["DiskStore"] = updatedJsonArray;
        localJsonBase.setObject(majorJsonObject);

        int indexOfDiskObject;
        for (int i = 0; i < diskVector.size(); i++) {
            if (diskVector.at(i).getId() == diskObject.value("Id").toString()) {
                indexOfDiskObject = i;
                break;
            }
        }

        diskVector.replace(indexOfDiskObject, Disk::fromJsonObject(diskObject));
        break;
    }
    }
    updateTableWidget();
}

void MainWindow::insertDiskIntoWidget(Disk disk)
{
    QString id = disk.getId();
    QString diskType = disk.getDiskType();
    QString name = disk.getName();
    QString author = disk.getAuthor();
    QString note = disk.getNote();
    QString price = disk.getPrice();

    if (elementVisibleInWidget(disk.getDiskType())) {
        ui->tableWidget->insertRow(ui->tableWidget->rowCount());
        int currentRow = ui->tableWidget->rowCount() - 1;

        ui->tableWidget->setItem(currentRow, 0, new QTableWidgetItem(id));
        ui->tableWidget->setItem(currentRow, 1, new QTableWidgetItem(diskType));
        ui->tableWidget->setItem(currentRow, 2, new QTableWidgetItem(name));
        ui->tableWidget->setItem(currentRow, 3, new QTableWidgetItem(author));
        ui->tableWidget->setItem(currentRow, 4, new QTableWidgetItem(note));
        ui->tableWidget->setItem(currentRow, 5, new QTableWidgetItem(price));
    }
}

QString MainWindow::makeDoubleTextLineCorrect(QString text)
{
    if (text == "0.0" || text == "0.") {
        return "0";
    } else if (text.contains(QRegExp("[0-9]+\\.[0-9]$"))) {
        return text + "0";
    } else if (text.contains(QRegExp("[0-9]+\\.$"))) {
        return text + "00";
    } else if (text.contains(QRegExp("[0-9]+\\.[0-9]{2}$"))) {
        return text;
    }

    return text + ".00";
}

bool caseInsensitiveSortingByName(const Disk &disk1, const Disk &disk2)
{
    return disk1.getName().toLower() < disk2.getName().toLower();
}
bool caseInsensitiveSortingByAuthor(const Disk &disk1, const Disk &disk2)
{
    return disk1.getAuthor().toLower() < disk2.getAuthor().toLower();
}
bool sortingByPrice(const Disk &disk1, const Disk &disk2)
{
    return disk1.getPrice().toDouble() < disk2.getPrice().toDouble();
}

QVector<Disk> MainWindow::sortDiskVector(MainWindow::SortOption option)
{
    QVector<Disk> tempDiskVector = diskVector;
    switch (option) {
    case MainWindow::SortOption::NAME: {
        qSort(tempDiskVector.begin(), tempDiskVector.end(), caseInsensitiveSortingByName);
        break;
    }
    case MainWindow::SortOption::AUTHOR: {
        qSort(tempDiskVector.begin(), tempDiskVector.end(), caseInsensitiveSortingByAuthor);
        break;
    }
    case MainWindow::SortOption::PRICE: {
        qSort(tempDiskVector.begin(), tempDiskVector.end(), sortingByPrice);
        break;
    }
    default: {
        break;
    }
    }

    return tempDiskVector;
}

void MainWindow::on_openButton_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Choose Base", "/home", "(*.json)");

    if (!fileName.isEmpty()) {
        diskVector.clear();
        databaseOpenFile.setFileName(fileName);
        databaseOpenFile.open(QIODevice::ReadOnly);
        localJsonBase = QJsonDocument::fromJson(databaseOpenFile.readAll());
        databaseOpenFile.close();
        QJsonArray jsonArray = QJsonValue(localJsonBase.object().value("DiskStore")).toArray();
        for (int i = 0; i < jsonArray.size(); i++) {
            diskVector.push_back(Disk::fromJsonObject(jsonArray.at(i).toObject()));
        }
        updateTableWidget();
    }
}

void MainWindow::on_addButton_clicked()
{
    if (checkIfFillInAllInputFields()) {
        QString diskType = Disk::typeInformation.at(ui->diskTypeComboBox->currentIndex() - 1);
        QString name = ui->nameField->text();
        QString author = ui->authorField->text();
        QString note = ui->noteField->text();
        QString price = makeDoubleTextLineCorrect(ui->priceField->text());

        Disk disk(QUuid::createUuid().toString(QUuid::Id128), diskType, name, author, note, price);
        updateBase(disk.toJsonObject(), DocOptions::ADD);
        clearInputFields();

    } else {
        QMessageBox::warning(this, "Disk Store", "Please, fill in all fields!");
    }
}

bool MainWindow::containsAllSearchedWords(QVector<QString> searchedWords, QString diskToString)
{
    foreach (QString singleWord, searchedWords) {
        QString pattern = "\\b" + singleWord + "\\b";
        if (!diskToString.contains(QRegExp(pattern))) {
            return false;
        }
    }
    return true;
}

void MainWindow::on_searchButton_clicked()
{
    if (!ui->searchField->text().isEmpty()) {
        on_resetButton_clicked();
        ui->tableWidget->setRowCount(0);
        QVector<QString> searchingWords = ui->searchField->text().toLower().split(" ").toVector();
        foreach (Disk disk, diskVector) {
            QString diskData = disk.toString().toLower();
            if (containsAllSearchedWords(searchingWords, diskData)) {
                insertDiskIntoWidget(disk);
            }
        }

        ui->searchField->clear();
    } else {
        QMessageBox::warning(this, "Disk Store", "Fill in the search field!");
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
        ui->diskTypeComboBox->setCurrentIndex(
            Disk::typeInformation.indexOf(
                ui->tableWidget->model()->index(modelIndex.row(), 1).data().toString())
            + 1);
        ui->nameField->setText(
            ui->tableWidget->model()->index(modelIndex.row(), 2).data().toString());
        ui->authorField->setText(
            ui->tableWidget->model()->index(modelIndex.row(), 3).data().toString());
        ui->noteField->setText(
            ui->tableWidget->model()->index(modelIndex.row(), 4).data().toString());
        ui->priceField->setText(
            ui->tableWidget->model()->index(modelIndex.row(), 5).data().toString());

        uiSwitcherWhileEditing(false);
    } else {
        QMessageBox::warning(this, "Disk Store", "Please, select a row to edit!");
    }
}

void MainWindow::on_saveChangesButton_clicked()
{
    QItemSelectionModel *selectedModel = ui->tableWidget->selectionModel();
    QModelIndex modelIndex = selectedModel->currentIndex();

    if (checkIfFillInAllInputFields()) {
        QString id = ui->tableWidget->model()->index(modelIndex.row(), 0).data().toString();
        QString diskType = Disk::typeInformation.at(ui->diskTypeComboBox->currentIndex() - 1);
        QString name = ui->nameField->text();
        QString author = ui->authorField->text();
        QString note = ui->noteField->text();
        QString price = makeDoubleTextLineCorrect(ui->priceField->text());

        Disk disk(id, diskType, name, author, note, price);
        updateBase(disk.toJsonObject(), DocOptions::EDIT);
        uiSwitcherWhileEditing(true);
        clearInputFields();

    } else {
        QMessageBox::warning(this, "Disk Store", "Please, fill in all fields!");
    }
}

void MainWindow::on_deleteButton_clicked()
{
    QItemSelectionModel *selectionModel = ui->tableWidget->selectionModel();
    if (selectionModel->hasSelection()) {
        QModelIndex modelIndex = selectionModel->currentIndex();

        QString id = ui->tableWidget->model()->index(modelIndex.row(), 0).data().toString();
        QString diskType = ui->tableWidget->model()->index(modelIndex.row(), 1).data().toString();
        QString name = ui->tableWidget->model()->index(modelIndex.row(), 2).data().toString();
        QString author = ui->tableWidget->model()->index(modelIndex.row(), 3).data().toString();
        QString note = ui->tableWidget->model()->index(modelIndex.row(), 4).data().toString();
        QString price = ui->tableWidget->model()->index(modelIndex.row(), 5).data().toString();

        Disk disk(id, diskType, name, author, note, price);
        updateBase(disk.toJsonObject(), DocOptions::DELETE);
        clearTableSelection();
    } else {
        QMessageBox::warning(this, "Disk Store", "Please, select a row to delete!");
    }
}

void MainWindow::on_saveButton_clicked()
{
    if (databaseOpenFile.exists()) {
        databaseOpenFile.open(QIODevice::WriteOnly);
        databaseSaveFile.resize(0);
        databaseOpenFile.write(localJsonBase.toJson());
        databaseOpenFile.close();

        QMessageBox::information(this, "Disk Store", "Saved successfully!");
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
            QMessageBox::information(this, "Disk Store", "Saved successfully!");
        }
    }
}

void MainWindow::on_saveAsButton_clicked()
{
    QString databaseName = "Disk Store DB (" + QDateTime::currentDateTime().toString("dd.MM.yyyy")
                           + ").json";
    QString fileName = QFileDialog::getSaveFileName(this, "Save DataBase", databaseName, "*.json");
    if (!fileName.isEmpty()) {
        databaseSaveFile.setFileName(fileName);
        databaseSaveFile.open(QIODevice::WriteOnly);
        databaseSaveFile.resize(0);
        databaseSaveFile.write(localJsonBase.toJson());
        databaseSaveFile.close();
        QMessageBox::information(this, "Disk Store", "Saved successfully!");
    }
}

void MainWindow::on_applyFilters_clicked()
{
    updateTableWidget();
}

void MainWindow::on_resetButton_clicked()
{
    ui->gameCheckBox->setChecked(true);
    ui->filmCheckBox->setChecked(true);
    ui->musicCheckBox->setChecked(true);
    ui->photoCheckBox->setChecked(true);
    ui->softCheckBox->setChecked(true);
    ui->utilityCheckBox->setChecked(true);
    ui->orderByComboBox->setCurrentIndex(0);
    updateTableWidget();
}
