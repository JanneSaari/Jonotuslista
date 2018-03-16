#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDockWidget>

#include "mainwidget.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void createMenus();
    void createDockWidgets();

private:
    MainWidget *mainWidget;
    QDockWidget *bottomDockWidget;
};

#endif // MAINWINDOW_H
