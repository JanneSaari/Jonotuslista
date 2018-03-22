#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include "currentclientstable.h"
#include "queuetable.h"
#include "adddialog.h"

#include <QTabWidget>
#include <QSortFilterProxyModel>
#include <QItemSelection>

class MainWindow;
class QSortFilterProxyModel;
class QAbstractTableModel;

class MainWidget : public QTabWidget
{
    Q_OBJECT

public:
    MainWidget();
    ~MainWidget();

public slots:
    void showAddDialog();
    void editPerson();
    void removePerson();

signals:
    void selectionChanged(const QItemSelection &selected);

private:
    void setupCurrentClientsTable();
    void setupQueueTable();
    void addPerson(const Person person);
    void addPersonToQueue(const Person person);

    QWidget *parent;
    CurrentClientsTable *currentClientsTable;
    QueueTable *queueTable;
    QSortFilterProxyModel *currentClientsProxyModel;
    QSortFilterProxyModel *queuedClientsProxyModel;
};

#endif // MAINWIDGET_H
