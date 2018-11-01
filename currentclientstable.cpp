/****************************************************************************
MIT License

Copyright (c) 2018 Janne Saari

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
****************************************************************************/

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
    return CurrentClientsTable::MaxColumn;
}

QVariant CurrentClientsTable::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (index.row() >= listOfPeople.size() || index.row() < 0)
        return QVariant();

    if (role == Qt::DisplayRole) {
        const auto &person = listOfPeople.at(index.row());

        if (index.column() == CurrentClientsTable::NameColumn) //Name
            return person.getName();
        else if(index.column() == CurrentClientsTable::StartingDateColumn) //Starting date
            return person.getStartingDate();
        else if(index.column() == CurrentClientsTable::EndingDateColumn) //Ending date
            return person.getEndingDate();
        else if(index.column() == CurrentClientsTable::DaysToEndColumn) //Days to ending date
            return QDate::currentDate().daysTo(person.getEndingDate());
        else if(index.column() == CurrentClientsTable::DaysToFullyearColumn) //Days to full year
            return QDate::currentDate().daysTo(person.getStartingDate().addYears(1));
        else if(index.column() == CurrentClientsTable::ValmentajaColumn) //Valmentaja
            return person.getOmaValmentaja();
        else if(index.column() == CurrentClientsTable::InfoColumn) //Info
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
        case CurrentClientsTable::NameColumn:
            return tr("Nimi");
        case CurrentClientsTable::StartingDateColumn:
            return tr("Aloituspäivä");
        case CurrentClientsTable::EndingDateColumn:
            return tr("Lopetuspäivä");
        case CurrentClientsTable::DaysToEndColumn:
            return tr("Päiviä jäljellä(3kk)");
        case CurrentClientsTable::DaysToFullyearColumn:
            return tr("Päiviä jäljellä(1v)");
        case CurrentClientsTable::ValmentajaColumn:
            return tr("OmaValmentaja");
        case CurrentClientsTable::InfoColumn:
            return tr("Lisätietoa");

        default:
            return QVariant();
        }
    }

    if (orientation == Qt::Vertical)
        return section + 1;

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

        if (index.column() == CurrentClientsTable::NameColumn)
            person.setName(value.toString());
        else if(index.column() == CurrentClientsTable::StartingDateColumn)
            person.setStartingDate(value.toDate());
        else if(index.column() == CurrentClientsTable::EndingDateColumn)
            person.setEndingDate(value.toDate());
        else if(index.column() == CurrentClientsTable::ValmentajaColumn)
            person.setOmaValmentaja(value.toString());
        else if(index.column() == CurrentClientsTable::InfoColumn)
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

void CurrentClientsTable::resetTable()
{
    if(!listOfPeople.isEmpty())
        removeRows(0, listOfPeople.size(), QModelIndex());
}

QVector<Person> CurrentClientsTable::getPeople()
{
    return listOfPeople;
}
