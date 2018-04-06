#ifndef PERSON_H
#define PERSON_H

#include <QDate>
#include <QDataStream>

class Person
{
public:
    Person();

    void setName(QString name);
    void setStartingDate(QDate date);
    void setEndingDate(QDate date);
    void setInfo(QString info);

    QString getName() const;
    QString getInfo() const;
    QDate getStartingDate() const;
    QDate getEndingDate() const;

    bool operator==(const Person &other) const
    {
        return name == other.name;
    }

    //These used to be private thats why setter and getters are used somewhere
    QString name;
    QDate startingDate;
    QDate endingDate;
    QString info;
    bool continues;
};

inline QDataStream &operator<<(QDataStream &stream, const Person &person)
{
    return stream << person.name << person.startingDate
                  << person.endingDate << person.info << person.continues;
}

inline QDataStream &operator>>(QDataStream &stream, Person &person)
{
    return stream >> person.name >> person.startingDate
                  >> person.endingDate >> person.info >> person.continues;
}

#endif // PERSON_H
