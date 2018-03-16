#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QHBoxLayout>
#include <QPushButton>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    resize(1200, 800);
    mainWidget = new MainWidget(this);
    setCentralWidget(mainWidget);
    createMenus();
    createDockWidgets();
}

MainWindow::~MainWindow()
{
}

void MainWindow::createMenus()
{

}

void MainWindow::createDockWidgets()
{
    bottomDockWidget = new QDockWidget(this, Qt::Widget);
    bottomDockWidget->setAllowedAreas(Qt::BottomDockWidgetArea);
    addDockWidget(Qt::BottomDockWidgetArea, bottomDockWidget);

    QWidget *dockWidget = new QWidget(this);
    QPushButton *testiButton = new QPushButton("testi", this);
    QHBoxLayout *dockLayout = new QHBoxLayout(this);
    dockLayout->addWidget(testiButton);
    dockWidget->setLayout(dockLayout);
    bottomDockWidget->setWidget(dockWidget);
}
