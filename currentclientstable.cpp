#include "currentclientstable.h"

CurrentClientsTable::CurrentClientsTable(QObject *parent)
    :QAbstractTableModel(parent)
{
}

int CurrentClientsTable::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return listOfPeople.size();
}

int CurrentClientsTable::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return 7;
    /*
    0 Luku,
    1 Nimi,
    2 aloituspäivä,
    3 lopetuspäivä,
    (lopetuspäivä 1v),
    4 päiviä 3kk,
    5 päiviä 1v
    6 lisätietoa
    */
}

QVariant CurrentClientsTable::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (index.row() >= listOfPeople.size() || index.row() < 0)
        return QVariant();

    if (role == Qt::DisplayRole) {
        const auto &person = listOfPeople.at(index.row());

        if (index.column() == 0) //Number of people
            return index.row() + 1;
        else if (index.column() == 1) //Name
            return person.getName();
        else if(index.column() == 2) //Starting date
            return person.getStartingDate();
        else if(index.column() == 3) //Ending date
            return person.getEndingDate();
        else if(index.column() == 4) //Days to ending date
            return QDate::currentDate().daysTo(person.getEndingDate());
        else if(index.column() == 5) //Days to full year
            return QDate::currentDate().daysTo(person.getStartingDate().addYears(1));
        else if(index.column() == 6) //Info
            return person.getInfo();
    }
    return QVariant();
}

QVariant CurrentClientsTable::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole)
        return QVariant();

    if (orientation == Qt::Horizontal) {
        switch (section) {
        case 0:
            return tr("#");
        case 1:
            return tr("Nimi");
        case 2:
            return tr("Aloituspäivä");
        case 3:
            return tr("Lopetuspäivä");
        case 4:
            return tr("Päiviä jäljellä(3kk)");
        case 5:
            return tr("Päiviä jäljellä(1v)");
        case 6:
            return tr("Lisätietoa");

        default:
            return QVariant();
        }
    }
    return QVariant();
}

Qt::ItemFlags CurrentClientsTable::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::ItemIsEnabled;

    return QAbstractTableModel::flags(index) | Qt::ItemIsEditable;
}

bool CurrentClientsTable::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (index.isValid() && role == Qt::EditRole) {
        int row = index.row();

        auto person = listOfPeople.value(row);

        if (index.column() == 1)
            person.setName(value.toString());
        else if(index.column() == 2)
            person.setStartingDate(value.toDate());
        else if(index.column() == 3)
            person.setEndingDate(value.toDate());
        else if(index.column() == 6)
            person.setInfo(value.toString());
        else
            return false;

        listOfPeople.replace(row, person);
        emit(dataChanged(index, index));

        return true;
    }

    return false;
}

bool CurrentClientsTable::insertRows(int position, int rows, const QModelIndex &index)
{
    Q_UNUSED(index);
    beginInsertRows(QModelIndex(), position, position + rows - 1);

    for (int row = 0; row < rows; ++row) {
        listOfPeople.insert(position, Person());
    }

    endInsertRows();
    return true;
}

bool CurrentClientsTable::removeRows(int position, int rows, const QModelIndex &index)
{
    Q_UNUSED(index);
    beginRemoveRows(QModelIndex(), position, position + rows - 1);

    for(int row = 0; row < rows; ++row) {
        listOfPeople.removeAt(position);
    }

    endRemoveRows();
    return true;
}

QVector<Person> CurrentClientsTable::getPeople()
{
    return listOfPeople;
}
