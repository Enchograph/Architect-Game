#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "game.h"
#include "gameBoard.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    game = new Game(5,5,vsComptr,simple);
    board = new gameBoard(game, this);

    setCentralWidget(board);  // 设置 gameBoard 为中央小部件
    board->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);  // 使gameBoard在父窗口中可以扩展

    connect(ui->startButton, &QPushButton::clicked, this, &MainWindow::on_startButton_clicked);
    connect(ui->resetButton, &QPushButton::clicked, this, &MainWindow::on_resetButton_clicked);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete game;
    delete board;
}

void MainWindow::on_startButton_clicked()
{
    game->reset();
    board->update();
}

void MainWindow::on_resetButton_clicked()
{
    game->reset();
    board->update();
}
