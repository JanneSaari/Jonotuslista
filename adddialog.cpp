#include "adddialog.h"

AddDialog::AddDialog(bool editDate)
{
    //If editDate is true, opens date editing and continue fields,
    //otherwise opens simpler dialog window with just name and info fields
    //Simpler window is used when editing person in queue

    mainLayout = new QVBoxLayout(this);
    setLayout(mainLayout);
    formLayout = new QFormLayout();
    mainLayout->addLayout(formLayout);
    buttonLayout = new QHBoxLayout();
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
    continueLabel = new QLabel(tr("Jatkaako"), this);
    continueBox = new QCheckBox(this);
    formLayout->addRow(continueLabel, continueBox);

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
    connect(okButton, QPushButton::clicked, this, &AddDialog::accept);

    cancelButton = new QPushButton(tr("Peru"), this);
    buttonLayout->addWidget(cancelButton);
    connect(cancelButton, QPushButton::clicked, this, &AddDialog::reject);
}
