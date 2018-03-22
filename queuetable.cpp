#include "queuetable.h"

QueueTable::QueueTable(QObject *parent)
    :QAbstractTableModel(parent)
{
    //---------------------------
//    Person testi;
//    testi.setName(QString("joku nimi"));
//    testi.setStartingDate(QDate::currentDate());
//    listOfPeople.append(testi);
//    Person testi2;
//    testi2.setName("toinen nimi");
//    listOfPeople.append(testi2);
//    Person testi3;
//    testi3.setName("kolmas nimi");
//    listOfPeople.append(testi3);
//    Person testi4;
//    testi4.setName("neljäs nimi");
//    listOfPeople.append(testi4);
    //---------------------------------------
}

int QueueTable::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return listOfPeople.size();
}

int QueueTable::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return 2;
    //Paikka jonossa
    //Nimi
}

QVariant QueueTable::data(const QModelIndex &index, int role) const
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

QVariant QueueTable::headerData(int section, Qt::Orientation orientation, int role) const
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

Qt::ItemFlags QueueTable::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::ItemIsEnabled;

    return QAbstractTableModel::flags(index) | Qt::ItemIsEditable;
}

bool QueueTable::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (index.isValid() && role == Qt::EditRole) {
        int row = index.row();

        auto person = listOfPeople.value(row);

        if (index.column() == 1)
            person.setName(value.toString());
        else
            return false;

        listOfPeople.replace(row, person);
        emit(dataChanged(index, index));

        return true;
    }

    return false;
}

bool QueueTable::insertRows(int position, int rows, const QModelIndex &index)
{
    Q_UNUSED(index);
    beginInsertRows(QModelIndex(), position, position + rows - 1);

    for (int row = 0; row < rows; ++row) {
        listOfPeople.insert(position, Person());
    }

    endInsertRows();
    return true;
}

bool QueueTable::removeRows(int position, int rows, const QModelIndex &index)
{
    Q_UNUSED(index);
    beginRemoveRows(QModelIndex(), position, position + rows - 1);

    for(int row = 0; row < rows; ++row) {
        listOfPeople.removeAt(position);
    }

    endRemoveRows();
    return true;
}

QVector<Person> QueueTable::getListOfPeople()
{
    return listOfPeople;
}
