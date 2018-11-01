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

//MyProxy is used to make header for the currentClientsTable.
//Vertical header keeps numbering in order even after sorting the table.
class MyProxy : public QSortFilterProxyModel
{
    Q_OBJECT

public:
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
};

class MainWidget : public QTabWidget
{
    Q_OBJECT

public:
    MainWidget();
    ~MainWidget();

    Person getPerson(int tabNumber, int row);

public slots:
    //files are saved with .list and .listq extensions (for currentClient and queuedClients)
    void openFile();
    void saveFile();
    void newFile();
    void showAddDialog();
    int editSelectedPerson(bool editDate = true);
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
    void loadSettings();
    void saveSettings();


    CurrentClientsTable *currentClientsTable;
    QueueTable *queueTable;
    MyProxy *currentClientsProxyModel;
    QSortFilterProxyModel *queuedClientsProxyModel;
    QTableView *tableView;
    QTableView *queueTableView;

    QString lastLoadFile;
    QString lastSavedFile;
};

#endif // MAINWIDGET_H
