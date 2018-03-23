#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDockWidget>
#include <QHBoxLayout>
#include <QPushButton>

#include "mainwidget.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void createMenus();
    void createButtons();

public slots:
    void updateButtons();

private:
    MainWidget *mainWidget;
    QDockWidget *bottomDockWidget;
    QWidget *buttonWidget;
    QHBoxLayout *buttonLayout;
    QPushButton *addPersonButton;
    QPushButton *editPersonButton;
    QPushButton *removePersonButton;
    QPushButton *moveFromQueueButton;
};

#endif // MAINWINDOW_H
