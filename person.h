#ifndef PERSON_H
#define PERSON_H

#include <QDate>

class Person
{
public:
    Person();

    void setName(QString name);
    void setStartingDate(QDate date);
    void setEndingDate(QDate date);
    void setInfo(QString info);

    QString getName() const;
    QDate getStartingDate() const;
    QDate getEndingDate() const;
    QString getInfo() const;

    bool operator==(const Person &other) const
    {
        return name == other.name;
    }

private:
    QString name;
    QDate startingDate;
    QDate endingDate;
    QString info;
};

#endif // PERSON_H
