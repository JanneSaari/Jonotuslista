#include "queuetable.h"

QueueTable::QueueTable(QObject *parent)
    :QAbstractTableModel(parent)
{
}

int QueueTable::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return listOfPeople.size();
}

int QueueTable::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return 5;
    //Paikka jonossa
    //Nimi
    //Info
}

QVariant QueueTable::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (index.row() >= listOfPeople.size() || index.row() < 0)
        return QVariant();

    if (role == Qt::DisplayRole) {
        const auto &person = listOfPeople.at(index.row());

        if (index.column() == 0)
            return listOfPeople.indexOf(person) + 1;
        else if(index.column() == 1)
            return person.getName();
        else if(index.column() == 2)
            return person.getInfo();
        else if(index.column() == 3)
            return person.getStartingDate();
        else if(index.column() == 4)
            return person.getEndingDate();
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
            case 2:
                return tr("Info");
            case 3:
                return tr("Aloituspäivä");
            case 4:
                return tr("Lopetuspäivä");

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
        else if(index.column() == 2)
            person.setInfo(value.toString());
        else if(index.column() == 3)
            person.setStartingDate(value.toDate());
        else if(index.column() == 4)
            person.setEndingDate(value.toDate());
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

QVector<Person> QueueTable::getPeople()
{
    return listOfPeople;
}
