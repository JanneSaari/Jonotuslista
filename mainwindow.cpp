/****************************************************************************
MIT License

Copyright (c) 2018 Janne Saari

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
****************************************************************************/

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    resize(1200, 800);
    mainWidget = new MainWidget();
    setCentralWidget(mainWidget);
    createActions();
    createMenus();
    createButtons();
}

MainWindow::~MainWindow()
{
    delete mainWidget;
}

void MainWindow::createActions()
{
    newFileAct = new QAction(tr("&Uusi tiedosto"), this);
    connect(newFileAct, &QAction::triggered, mainWidget, &MainWidget::newFile);

    openAct = new QAction(tr("&Avaa..."), this);
    connect(openAct, &QAction::triggered, mainWidget, &MainWidget::openFile);

    saveAct = new QAction(tr("&Tallenna nimellä.."), this);
    connect(saveAct, &QAction::triggered, mainWidget, &MainWidget::saveFile);

    exitAct = new QAction(tr("&Sulje..."), this);
    connect(exitAct, &QAction::triggered, this, &QWidget::close);
}

void MainWindow::createMenus()
{
    fileMenu = menuBar()->addMenu(tr("&Tiedosto"));
    fileMenu->addAction(newFileAct);
    fileMenu->addSeparator();
    fileMenu->addAction(openAct);
    fileMenu->addAction(saveAct);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAct);
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
    connect(addPersonButton, &QPushButton::clicked, mainWidget, &MainWidget::showAddDialog);

    editPersonButton = new QPushButton(tr("Muokkaa"), this);
    buttonLayout->addWidget(editPersonButton);
    connect(editPersonButton, &QPushButton::clicked, mainWidget, &MainWidget::editSelectedPerson);

    removePersonButton = new QPushButton(tr("Poista"), this);
    buttonLayout->addWidget(removePersonButton);
    connect(removePersonButton, &QPushButton::clicked, mainWidget, &MainWidget::removePerson);

    moveFromQueueButton = new QPushButton(tr("Siirrä jonosta"), this);
    buttonLayout->addWidget(moveFromQueueButton);
    connect(moveFromQueueButton, &QPushButton::clicked, mainWidget, &MainWidget::moveFromQueue);
    moveFromQueueButton->setEnabled(false);

    connect(mainWidget, &QTabWidget::currentChanged, this, &MainWindow::updateButtons);
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
