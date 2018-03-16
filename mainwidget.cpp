#include <QTableView>
#include <QHeaderView>
#include <QtWidgets>

#include "mainwidget.h"

MainWidget::MainWidget(MainWindow *parent)
{
    currentClientsTable = new CurrentClientsTable(this);
    queuedClientsTable = new QueuedClientsTable(this);
    setupCurrentClientsTable();
    setupQueuedClientsTable();
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

void MainWidget::setupQueuedClientsTable()
{
    queuedClientsProxyModel = new QSortFilterProxyModel(this);
    queuedClientsProxyModel->setSourceModel(queuedClientsTable);

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
