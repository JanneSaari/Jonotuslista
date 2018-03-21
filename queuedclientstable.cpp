#include "queuedclientstable.h"

QueuedClientsTable::QueuedClientsTable(QObject *parent)
    :QAbstractTableModel(parent)
{
    //---------------------------
    Person testi;
    testi.setName(QString("joku nimi"));
    testi.setStartingDate(QDate::currentDate());
    listOfPeople.append(testi);
    Person testi2;
    testi2.setName("toinen nimi");
    listOfPeople.append(testi2);
    Person testi3;
    testi3.setName("kolmas nimi");
    listOfPeople.append(testi3);
    Person testi4;
    testi4.setName("neljäs nimi");
    listOfPeople.append(testi4);
    //---------------------------------------
}

int QueuedClientsTable::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return listOfPeople.size();
}

int QueuedClientsTable::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return 2;
    //Paikka jonossa
    //Nimi
}

QVariant QueuedClientsTable::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (index.row() >= listOfPeople.size() || index.row() < 0)
        return QVariant();

    if (role == Qt::DisplayRole) {
        const auto &person = listOfPeople.at(index.row());

        if (index.column() == 0) //
            return listOfPeople.indexOf(person) + 1;
        else if(index.column() == 1)
            return person.getName();
    }
    return QVariant();
}

QVariant QueuedClientsTable::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole)
        return QVariant();

    if (orientation == Qt::Horizontal) {
        switch (section) {
            case 0:
                return tr("Paikka jonossa");
            case 1:
                return tr("Nimi");

            default:
                return QVariant();
        }
    }
    return QVariant();
}

Qt::ItemFlags QueuedClientsTable::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::ItemIsEnabled;

    return QAbstractTableModel::flags(index) | Qt::ItemIsEditable;
}
