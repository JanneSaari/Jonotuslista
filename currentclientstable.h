#ifndef CURRENTCLIENTSTABLE_H
#define CURRENTCLIENTSTABLE_H

#include <QAbstractTableModel>
#include <QDate>
#include <QVector>

#include "person.h"

//TODO make enum for column numbers so that i dont have change numbers manually everytime something changes

class CurrentClientsTable : public QAbstractTableModel
{
    Q_OBJECT

public:
    CurrentClientsTable(QObject *parent = 0);

    int rowCount(const QModelIndex &parent) const override;
    int columnCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;
    bool insertRows(int position, int rows, const QModelIndex &index = QModelIndex()) override;
    bool removeRows(int position, int rows, const QModelIndex &index = QModelIndex()) override;
    QVector<Person> getPeople();

private:
    QVector<Person> listOfPeople;
};

#endif // CURRENTCLIENTSTABLE_H
