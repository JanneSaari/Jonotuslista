#ifndef QUEUETABLE_H
#define QUEUETABLE_H

#include <QAbstractTableModel>

#include "person.h"

class QueueTable : public QAbstractTableModel
{
    Q_OBJECT
public:
    QueueTable(QObject *parent = 0);

    int rowCount(const QModelIndex &parent) const override;
    int columnCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;
    bool insertRows(int position, int rows, const QModelIndex &index = QModelIndex()) override;
//    bool removeRows(int position, int rows, const QModelIndex &index = QModelIndex()) override;

private:
    QVector<Person> listOfPeople;
};

#endif // QUEUETABLE_H
