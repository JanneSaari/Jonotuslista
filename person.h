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
    void setOmaValmentaja(QString valmentaja);

    QString getName() const;
    QString getInfo() const;
    QDate getStartingDate() const;
    QDate getEndingDate() const;
    QString getOmaValmentaja() const;

    bool operator==(const Person &other) const
    {
        return name == other.name;
    }

    //These used to be private thats why setter and getters are used somewhere
    QString name;
    QDate startingDate;
    QDate endingDate;
    QString info;
    QString omaValmentaja;
};

inline QDataStream &operator<<(QDataStream &stream, const Person &person)
{
    return stream << person.name << person.startingDate
                  << person.endingDate << person.info << person.omaValmentaja;
}

inline QDataStream &operator>>(QDataStream &stream, Person &person)
{
    return stream >> person.name >> person.startingDate
                  >> person.endingDate >> person.info >> person.omaValmentaja;
}

#endif // PERSON_H
