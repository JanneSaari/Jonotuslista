/****************************************************************************
MIT License

Copyright (c) 2018 Janne Saari

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
****************************************************************************/

#include <QtWidgets>

#include "mainwidget.h"

QVariant MyProxy::headerData(int section, Qt::Orientation orientation, int role) const {
  if(orientation!=Qt::Vertical || role!=Qt::DisplayRole)
    return QSortFilterProxyModel::headerData(section, orientation, role);

  return section + 1;
}

MainWidget::MainWidget()
{
    currentClientsTable = new CurrentClientsTable(this);
    queueTable = new QueueTable(this);
    setupCurrentClientsTable();
    setupQueueTable();
    loadSettings();
    if(!lastLoadFile.isEmpty())
        readFromFile(lastLoadFile);
}

MainWidget::~MainWidget()
{
    saveSettings();
    currentClientsProxyModel->deleteLater();
    delete(currentClientsProxyModel);
}


void MainWidget::setupCurrentClientsTable()
{
    currentClientsProxyModel = new MyProxy();
    currentClientsProxyModel->setSourceModel(currentClientsTable);

    tableView = new QTableView(this);
    tableView->setModel(currentClientsProxyModel);

    tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    tableView->horizontalHeader()->setStretchLastSection(true);
    tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tableView->setSelectionMode(QAbstractItemView::SingleSelection);

    tableView->setSortingEnabled(true);
    tableView->sortByColumn(CurrentClientsTable::StartingDateColumn, Qt::AscendingOrder);

    connect(tableView->selectionModel(),
        &QItemSelectionModel::selectionChanged,
        this, &MainWidget::selectionChanged);

    connect(this, &QTabWidget::currentChanged, this, [this](int tabIndex) {
        auto *tableView = qobject_cast<QTableView *>(widget(tabIndex));
        if (tableView)
            emit selectionChanged(tableView->selectionModel()->selection());
    });

    addTab(tableView, "Henkilöt");
}

void MainWidget::setupQueueTable()
{
    queuedClientsProxyModel = new QSortFilterProxyModel(this);
    queuedClientsProxyModel->setSourceModel(queueTable);

    queueTableView = new QTableView(this);
    queueTableView->setModel(queuedClientsProxyModel);

    queueTableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    queueTableView->horizontalHeader()->setStretchLastSection(true);
    queueTableView->verticalHeader()->hide();
    queueTableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    queueTableView->setSelectionMode(QAbstractItemView::SingleSelection);

    queueTableView->setSortingEnabled(true);
    queueTableView->sortByColumn(QueueTable::NumberColumn, Qt::AscendingOrder);
    queueTableView->setColumnHidden(QueueTable::StartingDateColumn, true);
    queueTableView->setColumnHidden(QueueTable::EndingDateColumn, true);

    connect(queueTableView->selectionModel(),
        &QItemSelectionModel::selectionChanged,
        this, &MainWidget::selectionChanged);

    connect(this, &QTabWidget::currentChanged, this, [this](int tabIndex) {
        auto *queueTableView = qobject_cast<QTableView *>(widget(tabIndex));
        if (queueTableView)
            emit selectionChanged(queueTableView->selectionModel()->selection());
    });

    addTab(queueTableView, "Jono");
}

void MainWidget::showAddDialog()
{
    if(currentIndex() == 0) {
        AddDialog aDialog(true);
        aDialog.setWindowTitle(tr("Lisää Henkilö"));
        if(aDialog.exec()) {
            Person person;
            person.setName(aDialog.nameField->text());
            person.setStartingDate(aDialog.startingDate->date());
            person.setEndingDate(aDialog.endingDate->date());
            person.setInfo(aDialog.infoField->text());
            person.setOmaValmentaja(aDialog.valmentajaField->text());
            addPerson(person);
        }
    }
    else if(currentIndex() == 1) {
        AddDialog aDialog(false);
        aDialog.setWindowTitle(tr("Lisää Henkilö"));
        if(aDialog.exec()){
            Person person;
            person.setName(aDialog.nameField->text());
            person.setInfo(aDialog.infoField->text());
            addPersonToQueue(person);
        }
    }
}

void MainWidget::addPerson(const Person person)
{
    currentClientsTable->insertRows(0, 1, QModelIndex());

    QModelIndex index = currentClientsTable->index(0, CurrentClientsTable::NameColumn, QModelIndex());
    currentClientsTable->setData(index, person.getName(), Qt::EditRole);
    index = currentClientsTable->index(0, CurrentClientsTable::StartingDateColumn, QModelIndex());
    currentClientsTable->setData(index, person.getStartingDate(), Qt::EditRole);
    index = currentClientsTable->index(0, CurrentClientsTable::EndingDateColumn, QModelIndex());
    currentClientsTable->setData(index, person.getEndingDate(), Qt::EditRole);
    index = currentClientsTable->index(0, CurrentClientsTable::DaysToEndColumn, QModelIndex());
    currentClientsTable->setData(index, person.getEndingDate(), Qt::EditRole);
    index = currentClientsTable->index(0, CurrentClientsTable::DaysToFullyearColumn, QModelIndex());
    currentClientsTable->setData(index, person.getStartingDate().addYears(1), Qt::EditRole);
    index = currentClientsTable->index(0, CurrentClientsTable::ValmentajaColumn, QModelIndex());
    currentClientsTable->setData(index, person.getOmaValmentaja(), Qt::EditRole);
    index = currentClientsTable->index(0, CurrentClientsTable::InfoColumn, QModelIndex());
    currentClientsTable->setData(index, person.getInfo(), Qt::EditRole);
}

void MainWidget::addPersonToQueue(const Person person)
{
    queueTable->insertRows(queueTable->getPeople().size(), 1, QModelIndex());

    QModelIndex index = queueTable->index(queueTable->getPeople().size() - 1, QueueTable::NameColumn, QModelIndex());
    queueTable->setData(index, person.getName(), Qt::EditRole);
    index = queueTable->index(queueTable->getPeople().size() - 1, QueueTable::InfoColumn, QModelIndex());
    queueTable->setData(index, person.getInfo(), Qt::EditRole);
    index = queueTable->index(queueTable->getPeople().size() - 1, QueueTable::StartingDateColumn, QModelIndex());
    queueTable->setData(index, person.getStartingDate(), Qt::EditRole);
    index = queueTable->index(queueTable->getPeople().size() - 1, QueueTable::EndingDateColumn, QModelIndex());
    queueTable->setData(index, person.getEndingDate(), Qt::EditRole);
}

Person MainWidget::getPerson(int tabNumber, int row)
{
    Person person;
    if(tabNumber == 0)
        person = currentClientsTable->getPeople().at(row);
    else if(tabNumber == 1)
        person = queueTable->getPeople().at(row);
    return person;
}

//Set editDate to true if you want to open editDialog with date editing
//If false, opens simpler dialog with just name and info fields.
int MainWidget::editSelectedPerson(bool editDate)
{
    QTableView *temp = static_cast<QTableView*>(currentWidget());
    QSortFilterProxyModel *proxy = static_cast<QSortFilterProxyModel*>(temp->model());
    QItemSelectionModel *selectionModel = temp->selectionModel();
    QModelIndexList indexes = selectionModel->selectedRows();

    foreach (QModelIndex index, indexes) {
        int row = proxy->mapToSource(index).row();
        if(currentIndex() == 1) {
            if(openEditDialog(currentIndex(), row, editDate))
                return 1;
            else
                return 0;
            }
        else {
            if(openEditDialog(currentIndex(), row))
                return 1;
            else
                return 0;
        }
    }
    return 0;
}

void MainWidget::removePerson()
{
    QTableView *temp = static_cast<QTableView*>(currentWidget());
    QSortFilterProxyModel *proxy = static_cast<QSortFilterProxyModel*>(temp->model());
    QItemSelectionModel *selectionModel = temp->selectionModel();

    QModelIndexList indexes = selectionModel->selectedRows();

    foreach (QModelIndex index, indexes) {
        int row = proxy->mapToSource(index).row();
        if(currentIndex() == 0) {
            currentClientsTable->removeRows(row, 1, QModelIndex());
            if(!queueTable->getPeople().isEmpty()) {
                if(!openEditDialog(1, 0, true, "Muokkaa jonosta otettavaa henkilöä")){
                    break;
                }
                Person person = queueTable->getPeople().first();
                addPerson(person);
                queueTable->removeRow(queueTable->getPeople().indexOf(person), QModelIndex());
            }
            else {
                QMessageBox::information(this, tr("Tyhjä jono."), tr("Uutta henkilöä ei voitu ottaa jonosta, koska se on tyhjä."));
                return;
            }
        }
        else if(currentIndex() == 1)
            queueTable->removeRows(row, 1, QModelIndex());
    }
}

void MainWidget::moveFromQueue()
{
    if(currentIndex() == 1) {
        QTableView *temp = static_cast<QTableView*>(currentWidget());
        QSortFilterProxyModel *proxy = static_cast<QSortFilterProxyModel*>(temp->model());
        QItemSelectionModel *selectionModel = temp->selectionModel();

        QModelIndexList indexes = selectionModel->selectedRows();

        Person person;
        foreach (QModelIndex index, indexes) {
            int row = proxy->mapToSource(index).row();
            if(!editSelectedPerson(true))
                break; //If editing is cancelled, stop function from moving person from queue.
            person = getPerson(currentIndex(), row);
            addPerson(person);
            removePerson();
        }
    }
}

//If editDate is true, opens date editing and continue fields,
//otherwise opens simpler dialog window with just name and info fields
//Simpler window is used when editing person in queue
int MainWidget::openEditDialog(int tabNumber, int row, bool editDate, QString title)
{
    Person oldValues = getPerson(tabNumber, row);
    if(tabNumber == 1) {
        AddDialog editDialog(editDate);
        editDialog.setWindowTitle(title);

        editDialog.nameField->setText(oldValues.getName());
        editDialog.infoField->setText(oldValues.getInfo());
        if(editDate){
            editDialog.startingDate->setDate(oldValues.getStartingDate());
            editDialog.endingDate->setDate(oldValues.getEndingDate());
            editDialog.valmentajaField->setText(oldValues.getOmaValmentaja());
        }

        if(editDialog.exec()) {
            Person newValues;
            newValues.setName(editDialog.nameField->text());
            if(newValues.getName() != oldValues.getName()) {
                QModelIndex index = queueTable->index(row, QueueTable::NameColumn, QModelIndex());
                queueTable->setData(index, QVariant(newValues.getName()), Qt::EditRole);
            }
            newValues.setInfo(editDialog.infoField->text());
            if(newValues.getInfo() != oldValues.getInfo()) {
                QModelIndex index = queueTable->index(row, QueueTable::InfoColumn, QModelIndex());
                queueTable->setData(index, QVariant(newValues.getInfo()), Qt::EditRole);
            }
            if(editDate) {
                newValues.setStartingDate(editDialog.startingDate->date());
                if(newValues.getStartingDate() != oldValues.getStartingDate()) {
                    QModelIndex index = queueTable->index(row, QueueTable::StartingDateColumn, QModelIndex());
                    queueTable->setData(index, QVariant(newValues.getStartingDate()), Qt::EditRole);
                }
                newValues.setEndingDate(editDialog.endingDate->date());
                if(newValues.getEndingDate() != oldValues.getEndingDate()) {
                    QModelIndex index = queueTable->index(row, QueueTable::EndingDateColumn, QModelIndex());
                    queueTable->setData(index, QVariant(newValues.getEndingDate()), Qt::EditRole);
                }
                newValues.setOmaValmentaja(editDialog.valmentajaField->text());
                if(newValues.getOmaValmentaja() != oldValues.getOmaValmentaja()) {
                    QModelIndex index = queueTable->index(row, QueueTable::ValmentajaColumn, QModelIndex());
                    queueTable->setData(index, QVariant(newValues.getOmaValmentaja()), Qt::EditRole);
                }
            }
            return 1;
        }
        else
            return 0;
    }
    else {
        AddDialog editDialog(editDate);
        editDialog.setWindowTitle(title);

        editDialog.nameField->setText(oldValues.getName());
        editDialog.startingDate->setDate(oldValues.getStartingDate());
        editDialog.endingDate->setDate(oldValues.getEndingDate());
        editDialog.infoField->setText(oldValues.getInfo());
        editDialog.valmentajaField->setText(oldValues.getOmaValmentaja());

        if(editDialog.exec()) {
            Person newValues;
            newValues.setName(editDialog.nameField->text());
            if(newValues.getName() != oldValues.getName()) {
                QModelIndex index = currentClientsTable->index(row, CurrentClientsTable::NameColumn, QModelIndex());
                currentClientsTable->setData(index, QVariant(newValues.getName()), Qt::EditRole);
            }
            newValues.setStartingDate(editDialog.startingDate->date());
            if(newValues.getStartingDate() != oldValues.getStartingDate()) {
                QModelIndex index = currentClientsTable->index(row, CurrentClientsTable::StartingDateColumn, QModelIndex());
                currentClientsTable->setData(index, QVariant(newValues.getStartingDate()), Qt::EditRole);
                index = currentClientsTable->index(row, CurrentClientsTable::DaysToFullyearColumn, QModelIndex());
                currentClientsTable->setData(index, QVariant(QDate::currentDate().daysTo(newValues.getStartingDate().addYears(1))), Qt::EditRole);
            }
            newValues.setEndingDate(editDialog.endingDate->date());
            if(newValues.getEndingDate() != oldValues.getEndingDate()) {
                QModelIndex index = currentClientsTable->index(row, CurrentClientsTable::EndingDateColumn, QModelIndex());
                currentClientsTable->setData(index, QVariant(newValues.getEndingDate()), Qt::EditRole);
                index = currentClientsTable->index(row, CurrentClientsTable::DaysToEndColumn, QModelIndex());
                currentClientsTable->setData(index, QVariant(QDate::currentDate().daysTo(newValues.getEndingDate())), Qt::EditRole);
            }
            newValues.setOmaValmentaja(editDialog.valmentajaField->text());
            if(newValues.getOmaValmentaja() != oldValues.getOmaValmentaja()) {
                QModelIndex index = currentClientsTable->index(row, CurrentClientsTable::ValmentajaColumn, QModelIndex());
                currentClientsTable->setData(index, QVariant(newValues.getOmaValmentaja()), Qt::EditRole);
            }
            newValues.setInfo(editDialog.infoField->text());
            if(newValues.getInfo() != oldValues.getInfo()) {
                QModelIndex index = currentClientsTable->index(row, CurrentClientsTable::InfoColumn, QModelIndex());
                currentClientsTable->setData(index, QVariant(newValues.getInfo()), Qt::EditRole);
            }
            return 1;
        }
        else
            return 0;
    }
}

void MainWidget::openFile()
{
    QString filename = QFileDialog::getOpenFileName(this, tr("Avaa tiedosto"), QDir::currentPath(), tr("(*.list)"));
    if(!filename.isEmpty()) {
        readFromFile(filename);
    }
}

void MainWidget::saveFile()
{
    QString filename = QFileDialog::getSaveFileName(this, tr("Tallenna tiedosto"), QDir::currentPath(), tr("(*.list)"));
    if(!filename.isEmpty()) {
        writeToFile(filename);
    }
}

void MainWidget::newFile()
{
    currentClientsTable->resetTable();
    queueTable->resetTable();

    lastLoadFile.clear();
}

void MainWidget::readFromFile(QString fileName)
{
    QString temp = fileName;

    QFile currentFile(fileName);

    if (!currentFile.open(QIODevice::ReadOnly)) {
        QMessageBox::information(this, tr("Tiedostoa ei pystytty avaamaan."),
            currentFile.errorString());
        return;
    }

    QFile queueFile(fileName.append("q"));
    if (!queueFile.open(QIODevice::ReadOnly)) {
        QMessageBox::information(this, tr("Jonolistaa ei pystytty avaamaan."),
            queueFile.errorString());
        return;
    }

    currentClientsTable->resetTable();
    QVector<Person> listOfPeople;
    QDataStream currentIn(&currentFile);
    currentIn >> listOfPeople;

    for (const auto &person: qAsConst(listOfPeople))
        addPerson(person);

    queueTable->resetTable();
    QVector<Person> queueList;
    QDataStream queueIn(&queueFile);
    queueIn >> queueList;

    for (const auto &person: qAsConst(queueList))
        addPersonToQueue(person);

    lastLoadFile = temp;
}

void MainWidget::writeToFile(QString fileName)
{
    QString temp = fileName;

    QFile currentClients(fileName);
    if(!currentClients.fileName().endsWith(".list"))
        currentClients.setFileName(fileName.append(".list"));
    if (!currentClients.open(QIODevice::WriteOnly)) {
        QMessageBox::information(this, tr("Tiedostoa ei pystytty avaamaan."), currentClients.errorString());
        return;
    }

    QFile queueFile(fileName.append("q"));
    if (!queueFile.open(QIODevice::WriteOnly)) {
        QMessageBox::information(this, tr("Tiedostoa ei pystytty avaamaan."), queueFile.errorString());
        return;
    }

    QDataStream currentOut(&currentClients);
    currentOut << currentClientsTable->getPeople();

    QDataStream queueOut(&queueFile);
    queueOut << queueTable->getPeople();

    lastSavedFile = temp;
}

void MainWidget::saveSettings()
{
    QFile settingsFile("settings");
    if(!settingsFile.open(QIODevice::WriteOnly)) {
        return;
    }
    QDataStream out(&settingsFile);
    out << lastLoadFile << lastSavedFile;
}

void MainWidget::loadSettings()
{
    QFile settingsFile("settings");
    if(!settingsFile.open(QIODevice::ReadOnly)) {
        return;
    }
    QDataStream in(&settingsFile);
    in >> lastLoadFile >> lastSavedFile;
}
