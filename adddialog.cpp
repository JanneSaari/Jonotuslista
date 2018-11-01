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

#include "adddialog.h"

AddDialog::AddDialog(bool editDate)
{
    //If editDate is true, opens editing fields for date and continue,
    //otherwise opens simpler dialog window with just name and info fields
    //Simpler window is used when editing person in queue

    mainLayout = new QVBoxLayout(this);
    setLayout(mainLayout);
    formLayout = new QFormLayout(this);
    mainLayout->addLayout(formLayout);
    buttonLayout = new QHBoxLayout(this);
    mainLayout->addLayout(buttonLayout);

    createTextFields();
    if(editDate)
        createDateFields();
    createButtons();
}

AddDialog::~AddDialog()
{
    delete formLayout;
    delete buttonLayout;
}

void AddDialog::createTextFields()
{
    nameLabel = new QLabel(tr("Nimi"), this);
    nameField = new QLineEdit(this);
    formLayout->addRow(nameLabel, nameField);
    infoLabel = new QLabel(tr("Lisätietoa"), this);
    infoField = new QLineEdit(this);
    formLayout->addRow(infoLabel, infoField);
}

void AddDialog::createDateFields()
{
    valmentajaLabel = new QLabel(tr("OmaValmentaja"), this);
    valmentajaField = new QLineEdit(this);
    formLayout->addRow(valmentajaLabel, valmentajaField);

    startingDateLabel = new QLabel(tr("Aloituspäivä"), this);
    startingDate = new QDateEdit(QDate::currentDate(), this);
    formLayout->addRow(startingDateLabel, startingDate);

    endingDateLabel = new QLabel(tr("Lopetuspäivä"), this);
    endingDate = new QDateEdit(startingDate->date().addMonths(3) ,this);
    formLayout->addRow(endingDateLabel, endingDate);
}

void AddDialog::createButtons()
{
    okButton = new QPushButton(tr("OK"), this);
    buttonLayout->addWidget(okButton);
    connect(okButton, &QPushButton::clicked, this, &AddDialog::accept);

    cancelButton = new QPushButton(tr("Peru"), this);
    buttonLayout->addWidget(cancelButton);
    connect(cancelButton, &QPushButton::clicked, this, &AddDialog::reject);
}
