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

class AddDialog : public QDialog
{
public:
    AddDialog();

    QLineEdit *nameEdit;
    QDateEdit *startingDate;
    QDateEdit *endingDate;

private:
    void createButtons();
    void createEditFields();

    QVBoxLayout *mainLayout;
    QFormLayout *formLayout;
    QHBoxLayout *buttonLayout;
    QLabel *nameLabel;
    QLabel *startingDateLabel;
    QLabel *endingDateLabel;
    QPushButton *okButton;
    QPushButton *cancelButton;
};

#endif // ADDDIALOG_H
