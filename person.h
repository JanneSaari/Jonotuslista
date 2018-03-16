#ifndef PERSON_H
#define PERSON_H

#include <QDate>

class Person
{
public:
    Person();

    void setName(QString name);
    void setStartingDate(QDate date);

    QString getName() const;
    QDate getStartingDate() const;

private:
    QString name;
    QDate startingDate;
};

#endif // PERSON_H
