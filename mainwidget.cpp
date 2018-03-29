#include <QTableView>
#include <QHeaderView>
#include <QtWidgets>

#include "mainwidget.h"

MainWidget::MainWidget()
{
    currentClientsTable = new CurrentClientsTable(this);
    queueTable = new QueueTable(this);
    setupCurrentClientsTable();
    setupQueueTable();
    readFromFile("Jonotuslista");
}

MainWidget::~MainWidget()
{
    writeToFile("Jonotuslista");
}

Person MainWidget::getPerson(int row)
{
    Person person;
    if(currentIndex() == 0) {
        QModelIndex nameIndex = currentClientsTable->index(row, 1, QModelIndex());
        QVariant varName = currentClientsTable->data(nameIndex, Qt::DisplayRole);
        person.setName(varName.toString());
        QModelIndex startDateIndex = currentClientsTable->index(row, 2, QModelIndex());
        QVariant varStartDate = currentClientsTable->data(startDateIndex, Qt::DisplayRole);
        person.setStartingDate(varStartDate.toDate());
        QModelIndex endDateIndex = currentClientsTable->index(row, 3, QModelIndex());
        QVariant varEndDate = currentClientsTable->data(endDateIndex, Qt::DisplayRole);
        person.setEndingDate(varEndDate.toDate());
        QModelIndex infoIndex = currentClientsTable->index(row, 6, QModelIndex());
        QVariant varInfo = currentClientsTable->data(infoIndex, Qt::DisplayRole);
        person.setInfo(varInfo.toString());
    }
    else if(currentIndex() == 1) {
        QModelIndex nameIndex = queueTable->index(row, 1, QModelIndex());
        QVariant varName = queueTable->data(nameIndex, Qt::DisplayRole);
        person.setName(varName.toString());
        QModelIndex infoIndex = queueTable->index(row, 2, QModelIndex());
        QVariant varInfo = queueTable->data(infoIndex, Qt::DisplayRole);
        person.setInfo(varInfo.toString());
        QModelIndex startDateIndex = queueTable->index(row, 3, QModelIndex());
        QVariant varStartDate = queueTable->data(startDateIndex, Qt::DisplayRole);
        person.setStartingDate(varStartDate.toDate());
        QModelIndex endDateIndex = queueTable->index(row, 4, QModelIndex());
        QVariant varEndDate = queueTable->data(endDateIndex, Qt::DisplayRole);
        person.setEndingDate(varEndDate.toDate());
    }

    return person;
}

void MainWidget::setupCurrentClientsTable()
{
    currentClientsProxyModel = new QSortFilterProxyModel(this);
    currentClientsProxyModel->setSourceModel(currentClientsTable);

    QTableView *tableView = new QTableView;
    tableView->setModel(currentClientsProxyModel);

    tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    tableView->horizontalHeader()->setStretchLastSection(true);
    tableView->verticalHeader()->hide();
    tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tableView->setSelectionMode(QAbstractItemView::SingleSelection);

    tableView->setSortingEnabled(true);

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

    QTableView *tableView = new QTableView;
    tableView->setModel(queuedClientsProxyModel);

    tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    tableView->horizontalHeader()->setStretchLastSection(true);
    tableView->verticalHeader()->hide();
    tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tableView->setSelectionMode(QAbstractItemView::SingleSelection);

    tableView->setSortingEnabled(true);

    connect(tableView->selectionModel(),
        &QItemSelectionModel::selectionChanged,
        this, &MainWidget::selectionChanged);

    connect(this, &QTabWidget::currentChanged, this, [this](int tabIndex) {
        auto *tableView = qobject_cast<QTableView *>(widget(tabIndex));
        if (tableView)
            emit selectionChanged(tableView->selectionModel()->selection());
    });

    addTab(tableView, "Jono");
}

void MainWidget::showAddDialog()
{
    AddDialog aDialog;
    aDialog.setWindowTitle(tr("Lisää Henkilö"));
    if(aDialog.exec()){
        Person person;
        person.setName(aDialog.nameField->text());
        person.setStartingDate(aDialog.startingDate->date());
        person.setEndingDate(aDialog.endingDate->date());
        person.setInfo(aDialog.infoField->text());

        if(currentIndex() == 0)
            addPerson(person);
        else if(currentIndex() == 1)
            addPersonToQueue(person);
    }
}

void MainWidget::addPerson(const Person person)
{
    currentClientsTable->insertRows(0, 1, QModelIndex());

    QModelIndex index = currentClientsTable->index(0, 0, QModelIndex());
    currentClientsTable->setData(index, currentClientsTable->getPeople().indexOf(person) + 1, Qt::EditRole);
    index = currentClientsTable->index(0, 1, QModelIndex());
    currentClientsTable->setData(index, person.getName(), Qt::EditRole);
    index = currentClientsTable->index(0, 2, QModelIndex());
    currentClientsTable->setData(index, person.getStartingDate(), Qt::EditRole);
    index = currentClientsTable->index(0, 3, QModelIndex());
    currentClientsTable->setData(index, person.getEndingDate(), Qt::EditRole);
    index = currentClientsTable->index(0, 4, QModelIndex());
    currentClientsTable->setData(index, person.getEndingDate(), Qt::EditRole);
    index = currentClientsTable->index(0, 5, QModelIndex());
    currentClientsTable->setData(index, person.getStartingDate().addYears(1), Qt::EditRole);
    index = currentClientsTable->index(0, 6, QModelIndex());
    currentClientsTable->setData(index, person.getInfo(), Qt::EditRole);
}

void MainWidget::addPersonToQueue(const Person person)
{
    queueTable->insertRows(queueTable->getPeople().size(), 1, QModelIndex());

    QModelIndex index = queueTable->index(queueTable->getPeople().size() - 1, 1, QModelIndex());
    queueTable->setData(index, person.getName(), Qt::EditRole);
    index = queueTable->index(queueTable->getPeople().size() - 1, 2, QModelIndex());
    queueTable->setData(index, person.getInfo(), Qt::EditRole);
    index = queueTable->index(queueTable->getPeople().size() - 1, 3, QModelIndex());
    queueTable->setData(index, person.getStartingDate(), Qt::EditRole);
    index = queueTable->index(queueTable->getPeople().size() - 1, 4, QModelIndex());
    queueTable->setData(index, person.getEndingDate(), Qt::EditRole);
}

void MainWidget::editSelectedPerson()
{
    QTableView *temp = static_cast<QTableView*>(currentWidget());
    QSortFilterProxyModel *proxy = static_cast<QSortFilterProxyModel*>(temp->model());
    QItemSelectionModel *selectionModel = temp->selectionModel();
    QModelIndexList indexes = selectionModel->selectedRows();

    Person person;
    foreach (QModelIndex index, indexes) {
        int row = proxy->mapToSource(index).row();

        person = getPerson(row);
        editValues(person, row);
    }
}

void MainWidget::removePerson()
{
    QTableView *temp = static_cast<QTableView*>(currentWidget());
    QSortFilterProxyModel *proxy = static_cast<QSortFilterProxyModel*>(temp->model());
    QItemSelectionModel *selectionModel = temp->selectionModel();

    QModelIndexList indexes = selectionModel->selectedRows();

    foreach (QModelIndex index, indexes) {
        int row = proxy->mapToSource(index).row();
        if(currentIndex() == 0)
            currentClientsTable->removeRows(row, 1, QModelIndex());
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
            editSelectedPerson();
            person = getPerson(row);
            addPerson(person);
            removePerson();
        }
    }
}

void MainWidget::editValues(Person oldValues, int row)
{
    AddDialog editDialog;
    editDialog.setWindowTitle(tr("Muokkaa Henkilöä"));

    editDialog.nameField->setText(oldValues.getName());
    editDialog.startingDate->setDate(oldValues.getStartingDate());
    editDialog.endingDate->setDate(oldValues.getEndingDate());
    editDialog.infoField->setText(oldValues.getInfo());

    if(editDialog.exec()) {
        Person newValues;
        if(currentIndex() == 0) {
            newValues.setName(editDialog.nameField->text());
            if(newValues.getName() != oldValues.getName()) {
                QModelIndex index = currentClientsTable->index(row, 0, QModelIndex());
                currentClientsTable->setData(index, QVariant(newValues.getName()), Qt::EditRole);
            }
            newValues.setStartingDate(editDialog.startingDate->date());
            if(newValues.getStartingDate() != oldValues.getStartingDate()) {
                QModelIndex index = currentClientsTable->index(row, 1, QModelIndex());
                currentClientsTable->setData(index, QVariant(newValues.getStartingDate()), Qt::EditRole);
                index = currentClientsTable->index(row, 4, QModelIndex());
                currentClientsTable->setData(index, QVariant(QDate::currentDate().daysTo(newValues.getStartingDate().addYears(1))), Qt::EditRole);
            }
            newValues.setEndingDate(editDialog.endingDate->date());
            if(newValues.getEndingDate() != oldValues.getEndingDate()) {
                QModelIndex index = currentClientsTable->index(row, 2, QModelIndex());
                currentClientsTable->setData(index, QVariant(newValues.getEndingDate()), Qt::EditRole);
                index = currentClientsTable->index(row, 3, QModelIndex());
                currentClientsTable->setData(index, QVariant(QDate::currentDate().daysTo(newValues.getEndingDate())), Qt::EditRole);
            }
            newValues.setInfo(editDialog.infoField->text());
            if(newValues.getInfo() != oldValues.getInfo()) {
                QModelIndex index = currentClientsTable->index(row, 5, QModelIndex());
                currentClientsTable->setData(index, QVariant(newValues.getInfo()), Qt::EditRole);
            }
        }
        if(currentIndex() == 1) {
            newValues.setName(editDialog.nameField->text());
            if(newValues.getName() != oldValues.getName()) {
                QModelIndex index = queueTable->index(row, 1, QModelIndex());
                queueTable->setData(index, QVariant(newValues.getName()), Qt::EditRole);
            }
            newValues.setInfo(editDialog.infoField->text());
            if(newValues.getInfo() != oldValues.getInfo()) {
                QModelIndex index = queueTable->index(row, 2, QModelIndex());
                queueTable->setData(index, QVariant(newValues.getInfo()), Qt::EditRole);
            }
            newValues.setStartingDate(editDialog.startingDate->date());
            if(newValues.getStartingDate() != oldValues.getStartingDate()) {
                QModelIndex index = queueTable->index(row, 3, QModelIndex());
                queueTable->setData(index, QVariant(newValues.getStartingDate()), Qt::EditRole);
            }
            newValues.setEndingDate(editDialog.endingDate->date());
            if(newValues.getEndingDate() != oldValues.getEndingDate()) {
                QModelIndex index = queueTable->index(row, 4, QModelIndex());
                queueTable->setData(index, QVariant(newValues.getEndingDate()), Qt::EditRole);
            }
        }
    }
}

void MainWidget::readFromFile(QString fileName)
{
    QFile currentFile(fileName);

    if (!currentFile.open(QIODevice::ReadOnly)) {
        QMessageBox::information(this, tr("Tiedostoa ei pystytty avaamaan."),
            currentFile.errorString());
        return;
    }

    QVector<Person> listOfPeople;
    QDataStream currentIn(&currentFile);
    currentIn >> listOfPeople;

//    if (listOfPeople.isEmpty()) {
//        QMessageBox::information(this, tr("Ei henkilöitä tiedostossa."),
//                                 tr("Tiedosto jonka yritit avata ei sisällä henkilöitä."));
//    } else {
    for (const auto &person: qAsConst(listOfPeople))
        addPerson(person);
//    }

    QFile queueFile(fileName.append("queue"));

    if (!queueFile.open(QIODevice::ReadOnly)) {
        QMessageBox::information(this, tr("Tiedostoa ei pystytty avaamaan."),
            queueFile.errorString());
        return;
    }

    QVector<Person> queueList;
    QDataStream queueIn(&queueFile);
    queueIn >> queueList;

//    if (queueList.isEmpty()) {
//        QMessageBox::information(this, tr("Ei henkilöitä tiedostossa."),
//                                 tr("Tiedosto jonka yritit avata ei sisällä henkilöitä."));
//    } else {
    for (const auto &person: qAsConst(queueList))
        addPersonToQueue(person);
//    }
}

void MainWidget::writeToFile(QString fileName)
{
    QFile currentClients(fileName);

    if (!currentClients.open(QIODevice::WriteOnly)) {
        QMessageBox::information(this, tr("Tiedostoa ei pystytty avaamaan."), currentClients.errorString());
        return;
    }

    QDataStream currentOut(&currentClients);
    currentOut << currentClientsTable->getPeople();

    QFile queueFile(fileName.append("queue"));

    if (!queueFile.open(QIODevice::WriteOnly)) {
        QMessageBox::information(this, tr("Tiedostoa ei pystytty avaamaan."), queueFile.errorString());
        return;
    }

    QDataStream queueOut(&queueFile);
    queueOut << queueTable->getPeople();
}
