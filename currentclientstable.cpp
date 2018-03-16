#include "tablemodel.h"

TableModel::TableModel(QObject *parent)
    :QAbstractTableModel(parent)
{

}

int TableModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return listOfPeople.size();
}

int TableModel::columnCount(const QModelIndex &parent) const
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

QVariant TableModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (index.row() >= listOfPeople.size() || index.row() < 0)
        return QVariant();

    if (role == Qt::DisplayRole) {
        const auto &person = listOfPeople.at(index.row());

        if (index.column() == 0)
            return person.name;
        else if(index.column() == 1)
            return person.startingDate;
        else if(index.column() == 2)
            return person.name;
        else if(index.column() == 3)
            return person.name;
        else if(index.column() == 4)
            return person.name;
    }
    return QVariant();
}

QVariant TableModel::headerData(int section, Qt::Orientation orientation, int role) const
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

Qt::ItemFlags TableModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::ItemIsEnabled;

    return QAbstractTableModel::flags(index) | Qt::ItemIsEditable;
}
