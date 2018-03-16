#include "person.h"

Person::Person()
{
}

void Person::setName(QString name)
{
    this->name = name;
}

void Person::setStartingDate(QDate date)
{
    startingDate = date;
}

void Person::setEndingDate(QDate date)
{
    endingDate = date;
}

QString Person::getName() const
{
    return name;
}

QDate Person::getStartingDate() const
{
    return startingDate;
}

QDate Person::getEndingDate() const
{
    return endingDate;
}
