#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    resize(1200, 800);
    mainWidget = new MainWidget(this);
    setCentralWidget(mainWidget);
}

MainWindow::~MainWindow()
{
}
