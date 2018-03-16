#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include "tablemodel.h"

#include <QTabWidget>
#include <QSortFilterProxyModel>
#include <QItemSelection>

class MainWindow;
class QSortFilterProxyModel;

class MainWidget : public QTabWidget
{
    Q_OBJECT

public:
    MainWidget(MainWindow *parent = 0);
    ~MainWidget();

signals:
    void selectionChanged(const QItemSelection &selected);

private:
    void setupListView();

    QWidget *parent;
    TableModel *table;
    QSortFilterProxyModel *proxyModel;
};

#endif // MAINWIDGET_H
