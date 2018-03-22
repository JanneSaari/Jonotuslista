#include "currentclientstable.h"

CurrentClientsTable::CurrentClientsTable(QObject *parent)
    :QAbstractTableModel(parent)
{
    //---------------------------
//    Person testi;
//    testi.setName(QString("joku nimi"));
//    //testi.setStartingDate(QDate::currentDate());
//    testi.setStartingDate(QDate(2018, 2, 16));
//    testi.setEndingDate(testi.getStartingDate().addMonths(3));
//    listOfPeople.append(testi);
    //---------------------------------------
}

int CurrentClientsTable::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return listOfPeople.size();
}

int CurrentClientsTable::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return 5;
    /*Nimi,
    aloituspäivä,
    lopetuspäivä,
    (lopetuspäivä 1v),
    päiviä 3kk,
    päiviä 1v*/
}

QVariant CurrentClientsTable::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (index.row() >= listOfPeople.size() || index.row() < 0)
        return QVariant();

    if (role == Qt::DisplayRole) {
        const auto &person = listOfPeople.at(index.row());

        if (index.column() == 0) //Name
            return person.getName();
        else if(index.column() == 1) //Starting date
            return person.getStartingDate();
        else if(index.column() == 2) //Ending date
            return person.getEndingDate();
        else if(index.column() == 3) //Days to ending date
            return QDate::currentDate().daysTo(person.getEndingDate());
        else if(index.column() == 4) //Days to full year
            return QDate::currentDate().daysTo(person.getStartingDate().addYears(1));
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
                return tr("Nimi");
            case 1:
                return tr("Aloituspäivä");
            case 2:
                return tr("Lopetuspäivä");
            case 3:
                return tr("Päiviä jäljellä(3kk)");
            case 4:
                return tr("Päiviä jäljellä(1v)");

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

        if (index.column() == 0)
            person.setName(value.toString());
        else if(index.column() == 1)
            person.setStartingDate(value.toDate());
        else if(index.column() == 2)
            person.setEndingDate(value.toDate());
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
