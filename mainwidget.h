#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include "currentclientstable.h"
#include "queuetable.h"
#include "adddialog.h"

#include <QTabWidget>
#include <QSortFilterProxyModel>
#include <QItemSelection>
#include <QTableView>

class MainWindow;
class QSortFilterProxyModel;
class QAbstractTableModel;

class MainWidget : public QTabWidget
{
    Q_OBJECT

public:
    MainWidget();
    ~MainWidget();

    Person getPerson(int tabNumber, int row);

public slots:
    void showAddDialog();
    void editSelectedPerson(bool editDate = true);
    void removePerson();
    void moveFromQueue();

signals:
    void selectionChanged(const QItemSelection &selected);

private:
    void setupCurrentClientsTable();
    void setupQueueTable();
    void addPerson(const Person person);
    void addPersonToQueue(const Person person);
    int openEditDialog(int tabNumber, int row, bool editDate = true, QString title = tr("Muokkaa henkilöä"));
    void readFromFile(QString fileName);
    void writeToFile(QString fileName);

    CurrentClientsTable *currentClientsTable;
    QueueTable *queueTable;
    QSortFilterProxyModel *currentClientsProxyModel;
    QSortFilterProxyModel *queuedClientsProxyModel;
    QTableView *tableView;
    QTableView *queueTableView;
};

#endif // MAINWIDGET_H
