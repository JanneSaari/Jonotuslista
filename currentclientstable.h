#ifndef CURRENTCLIENTSTABLE_H
#define CURRENTCLIENTSTABLE_H

#include <QAbstractTableModel>
#include <QDate>
#include <QVector>

#include "person.h"

class CurrentClientsTable : public QAbstractTableModel
{
    Q_OBJECT

public:
    CurrentClientsTable(QObject *parent = 0);

    int rowCount(const QModelIndex &parent) const override;
    int columnCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;

private:
    QVector<Person> listOfPeople;
};

#endif // CURRENTCLIENTSTABLE_H
