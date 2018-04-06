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
#include <QCheckBox>

class AddDialog : public QDialog
{
public:
    AddDialog(bool editDate = true);
    ~AddDialog();

    QLineEdit *nameField;
    QLineEdit *infoField;
    QDateEdit *startingDate;
    QDateEdit *endingDate;
    QCheckBox *continueBox;

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
    QLabel *continueLabel;
    QPushButton *okButton;
    QPushButton *cancelButton;
};

#endif // ADDDIALOG_H
