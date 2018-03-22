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
}

MainWidget::~MainWidget()
{

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
    if(aDialog.exec()){
        Person person;
        person.setName(aDialog.nameEdit->text());
        person.setStartingDate(aDialog.startingDate->date());
        person.setEndingDate(aDialog.endingDate->date());

        addPerson(person);
    }
}

void MainWidget::addPerson(const Person person)
{
    currentClientsTable->insertRows(0, 1, QModelIndex());

    QModelIndex index = currentClientsTable->index(0, 0, QModelIndex());
    currentClientsTable->setData(index, person.getName(), Qt::EditRole);
    index = currentClientsTable->index(0, 1, QModelIndex());
    currentClientsTable->setData(index, person.getStartingDate(), Qt::EditRole);
    index = currentClientsTable->index(0, 2, QModelIndex());
    currentClientsTable->setData(index, person.getEndingDate(), Qt::EditRole);
}

void MainWidget::addPersonToQueue(const Person person)
{
    queueTable->insertRows(0, 1, QModelIndex());

    QModelIndex index = queueTable->index(0, 0, QModelIndex());
    queueTable->setData(index, person.getName(), Qt::EditRole);
    index = queueTable->index(0, 1, QModelIndex());
    queueTable->setData(index, person.getStartingDate(), Qt::EditRole);
    index = queueTable->index(0, 2, QModelIndex());
    queueTable->setData(index, person.getEndingDate(), Qt::EditRole);
}

void MainWidget::editPerson()
{

}

void MainWidget::removePerson()
{

}
