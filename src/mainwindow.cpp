#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "game.hpp"

#include <QDebug>


Game *game;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->textEdit->setReadOnly(true);
    centralWidget()->setStyleSheet("background-image: url(:/background/images/menu_background.jpg);");
    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(start_on_click()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::start_on_click()
{
    game = new Game(100,100, 100);
    setCentralWidget(game);
    resize(game->size());
}
