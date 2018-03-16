#include "person.h"

Person::Person()
{
}

void Person::setName(QString name)
{
    name = name;
}

void Person::setStartingDate(QDate date)
{
    startingDate = date;
}

QString Person::getName() const
{
    return name;
}

QDate Person::getStartingDate() const
{
    return startingDate;
}
