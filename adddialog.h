#ifndef ADDDIALOG_H
#define ADDDIALOG_H

#include <QDialog>
#include <QPushButton>
#include <QHBoxLayout>

class AddDialog : public QDialog
{
public:
    AddDialog();

private:
    void createButtons();

    QHBoxLayout *buttonLayout;
    QPushButton *okButton;
    QPushButton *cancelButton;
};

#endif // ADDDIALOG_H
