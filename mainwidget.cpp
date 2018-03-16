#include <QTableView>
#include <QHeaderView>
#include <QtWidgets>

#include "mainwidget.h"

MainWidget::MainWidget(MainWindow *parent)
{
    table = new TableModel(this);
    setupListView();
}

MainWidget::~MainWidget()
{

}

void MainWidget::setupListView()
{
    proxyModel = new QSortFilterProxyModel(this);
    proxyModel->setSourceModel(table);

    QTableView *tableView = new QTableView;
    tableView->setModel(proxyModel);

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
