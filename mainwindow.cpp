#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    mainWidget = new MainWidget(this);
    setCentralWidget(mainWidget);
}

MainWindow::~MainWindow()
{
}
