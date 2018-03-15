#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QTabWidget>
#include <QSortFilterProxyModel>

#include "tablemodel.h"

class MainWidget : public QTabWidget
{
    Q_OBJECT

public:
    MainWidget(QWidget *parent = 0);

signals:
    void selectionChanged(const QItemSelection &selected);

private:
    void setupListView();

    QWidget *parent;
    TableModel *table;
    QSortFilterProxyModel *proxyModel;
};

#endif // MAINWIDGET_H
