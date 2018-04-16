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

void Person::setInfo(QString info)
{
    this->info = info;
}

void Person::setOmaValmentaja(QString valmentaja)
{
    omaValmentaja = valmentaja;
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

QString Person::getInfo() const
{
    return info;
}

QString Person::getOmaValmentaja() const
{
    return omaValmentaja;
}
