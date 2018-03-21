#include "adddialog.h"

AddDialog::AddDialog()
{
    buttonLayout = new QHBoxLayout(this);
    setLayout(buttonLayout);

    createButtons();
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
