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

    QString name;
    QDate startingDate;
    QDate endingDate;
    QString info;
};

inline QDataStream &operator<<(QDataStream &stream, const Person &person)
{
    return stream << person.name << person.startingDate
                  << person.endingDate << person.info;
}

inline QDataStream &operator>>(QDataStream &stream, Person &person)
{
    return stream >> person.name >> person.startingDate
                  >> person.endingDate >> person.info;
}

#endif // PERSON_H
