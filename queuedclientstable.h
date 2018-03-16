#ifndef QUEUEDCLIENTSTABLE_H
#define QUEUEDCLIENTSTABLE_H

#include <QAbstractTableModel>

#include "person.h"

class QueuedClientsTable : public QAbstractTableModel
{
    Q_OBJECT
public:
    QueuedClientsTable(QObject *parent = 0);

    int rowCount(const QModelIndex &parent) const override;
    int columnCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;

private:
    QVector<Person> listOfPeople;
};

#endif // QUEUEDCLIENTSTABLE_H