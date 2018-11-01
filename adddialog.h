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

#ifndef ADDDIALOG_H
#define ADDDIALOG_H

#include <QDialog>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QLineEdit>
#include <QDateEdit>
#include <QLabel>

//Dialog window for adding and editing person.
//If editDate is true, opens dialog window with
//additional fields for editing date.
class AddDialog : public QDialog
{
public:
    AddDialog(bool editDate = true);
    ~AddDialog();

    QLineEdit *nameField;
    QLineEdit *infoField;
    QLineEdit *valmentajaField;
    QDateEdit *startingDate;
    QDateEdit *endingDate;

private:
    void createButtons();
    void createTextFields();
    void createDateFields();

    QVBoxLayout *mainLayout;
    QFormLayout *formLayout;
    QHBoxLayout *buttonLayout;
    QLabel *nameLabel;
    QLabel *infoLabel;
    QLabel *startingDateLabel;
    QLabel *endingDateLabel;
    QLabel *valmentajaLabel;
    QPushButton *okButton;
    QPushButton *cancelButton;
};

#endif // ADDDIALOG_H
