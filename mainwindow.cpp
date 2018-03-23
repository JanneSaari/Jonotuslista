#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    resize(1200, 800);
    mainWidget = new MainWidget();
    setCentralWidget(mainWidget);
    createMenus();
    createButtons();
}

MainWindow::~MainWindow()
{
    delete mainWidget;
}

void MainWindow::createMenus()
{

}

void MainWindow::createButtons()
{
    bottomDockWidget = new QDockWidget(this, Qt::Widget);
    bottomDockWidget->setAllowedAreas(Qt::BottomDockWidgetArea);
    addDockWidget(Qt::BottomDockWidgetArea, bottomDockWidget);
    bottomDockWidget->setFeatures(QDockWidget::NoDockWidgetFeatures);

    buttonWidget = new QWidget(this);
    buttonLayout = new QHBoxLayout(buttonWidget);
    bottomDockWidget->setWidget(buttonWidget);
    buttonWidget->setLayout(buttonLayout);

    addPersonButton = new QPushButton(tr("Lisää"), this);
    buttonLayout->addWidget(addPersonButton);
    connect(addPersonButton, QPushButton::clicked, mainWidget, &MainWidget::showAddDialog);

    editPersonButton = new QPushButton(tr("Muokkaa"), this);
    buttonLayout->addWidget(editPersonButton);
    connect(editPersonButton, QPushButton::clicked, mainWidget, &MainWidget::editPerson);

    removePersonButton = new QPushButton(tr("Poista"), this);
    buttonLayout->addWidget(removePersonButton);
    connect(removePersonButton, QPushButton::clicked, mainWidget, &MainWidget::removePerson);

    moveFromQueueButton = new QPushButton(tr("Siirrä jonosta"), this);
    buttonLayout->addWidget(moveFromQueueButton);
    connect(moveFromQueueButton, QPushButton::clicked, mainWidget, &MainWidget::moveFromQueue);
    moveFromQueueButton->setEnabled(false);

    connect(mainWidget, QTabWidget::currentChanged, this, &MainWindow::updateButtons);
}

void MainWindow::updateButtons()
{
    if(mainWidget->currentIndex() == 0) {
        moveFromQueueButton->setEnabled(false);
    }
    if(mainWidget->currentIndex() == 1) {
        moveFromQueueButton->setEnabled(true);
    }
}
