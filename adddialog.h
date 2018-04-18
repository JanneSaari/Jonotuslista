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
