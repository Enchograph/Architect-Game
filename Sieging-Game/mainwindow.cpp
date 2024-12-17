#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QScreen>
#include <QGuiApplication>
#include <QStackedWidget>
#include <QPropertyAnimation>
#include "gridSizeDialog.h"
#include "game.h"
#include "gameBoard.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow),
    boardWidget(nullptr),  // 初始化为空
        gridDialog(new gridSizeDialog(this)) // 初始化 gridSizeDialog
{
    ui->setupUi(this);

    // 设置窗口大小为屏幕宽度的 70% 和高度的 70%
    QScreen *screen = QGuiApplication::primaryScreen();
    QRect screenGeometry = screen->geometry();
    this->resize(screenGeometry.width() * 0.7, screenGeometry.height() * 0.7);

    // 设置默认显示的页面为 beginPage
    ui->contentPage->setCurrentWidget(ui->beginPage);

    dialog11 = new gridSizeDialog(this);
    dialog12 = new gridSizeDialog(this);
    dialog13 = new gridSizeDialog(this);
    dialog21 = new gridSizeDialog(this);
    dialog22 = new gridSizeDialog(this);
    dialog23 = new gridSizeDialog(this);

    // 连接 gridSizeDialog 的 accepted 信号到自定义槽函数
    connect(dialog11, &gridSizeDialog::accepted, this, [this]() { openGamePage(dialog11 ,InitialState::human, Difficulty::simple); });
    connect(dialog12, &gridSizeDialog::accepted, this, [this]() { openGamePage(dialog12 ,InitialState::human, Difficulty::medium); });
    connect(dialog13, &gridSizeDialog::accepted, this, [this]() { openGamePage(dialog13 ,InitialState::human, Difficulty::hard); });
    connect(dialog21, &gridSizeDialog::accepted, this, [this]() { openGamePage(dialog21 ,InitialState::player1, Difficulty::simple); });
    connect(dialog22, &gridSizeDialog::accepted, this, [this]() { openGamePage(dialog22 ,InitialState::player1, Difficulty::medium); });
    connect(dialog23, &gridSizeDialog::accepted, this, [this]() { openGamePage(dialog23 ,InitialState::player1, Difficulty::hard); });


       // 初始化 gamePage，后续添加 gameBoard
       ui->gamePage->setLayout(new QVBoxLayout);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::openGamePage(const gridSizeDialog * gridDialog,InitialState initialState,Difficulty difficulty)
{
    int gridSize = gridDialog->getGridSize(); // 获取用户选择的棋盘大小

    // 如果已经存在 gameBoard，先删除它（避免重复初始化）
    if (boardWidget) {
        delete boardWidget;
        boardWidget = nullptr;
    }

    // 初始化 gameBoard
    boardWidget = new gameBoard(new Game(gridSize,gridSize,initialState,difficulty), this);

    // 将 gameBoard 添加到 gamePage 的布局中
    ui->gamePage->layout()->addWidget(boardWidget);

    // 切换到 gamePage
    ui->contentPage->setCurrentWidget(ui->gamePage);
}


void MainWindow::switchPage(QWidget *targetPage)
{
    if (ui->contentPage->currentWidget() != targetPage) {
        int pageHeight = ui->contentPage->height();
        QWidget *currentPage = ui->contentPage->currentWidget();
        QPropertyAnimation *hideAnim = new QPropertyAnimation(currentPage, "geometry", this);
        QPropertyAnimation *showAnim = new QPropertyAnimation(targetPage, "geometry", this);

        int direction = getPageIndex(targetPage) < getPageIndex(currentPage) ? 1 : -1;

        // 设置隐藏当前页面的动画
        hideAnim->setDuration(500);
        hideAnim->setEasingCurve(QEasingCurve::Linear);
        hideAnim->setStartValue(currentPage->geometry());
        hideAnim->setEndValue(QRect(0, direction * pageHeight, currentPage->width(), currentPage->height()));

        // 设置显示目标页面的动画
        showAnim->setDuration(500);
        showAnim->setEasingCurve(QEasingCurve::Linear);
        showAnim->setStartValue(QRect(0, -direction * pageHeight, targetPage->width(), targetPage->height()));
        showAnim->setEndValue(QRect(0, 0, targetPage->width(), targetPage->height()));

        // 页面切换结束后开始显示动画
        connect(hideAnim, &QPropertyAnimation::finished, this, [=]() {
            ui->contentPage->setCurrentWidget(targetPage);
            showAnim->start();
        });

        hideAnim->start();
    }
}

int MainWindow::getPageIndex(QWidget *page)
{
    if (page == ui->beginPage) return 0;
    if (page == ui->vsComptrPage) return 1;
    if (page == ui->vsPeoplePage) return 2;
    if (page == ui->loginPage) return 3;
    if (page == ui->settingPage) return 4;
    return -1;
}

void MainWindow::on_vsComptrBtn_clicked() { switchPage(ui->vsComptrPage); }
void MainWindow::on_vsPeopleBtn_clicked() { switchPage(ui->vsPeoplePage); }
void MainWindow::on_mainPageBtn_clicked() { switchPage(ui->beginPage); }
void MainWindow::on_loginBtn_clicked() { switchPage(ui->loginPage); }
void MainWindow::on_settingsBtn_clicked() { switchPage(ui->settingPage); }

void MainWindow::on_pushButton_16_clicked(){ dialog11->exec(); }
void MainWindow::on_pushButton_17_clicked(){ dialog12->exec(); }
void MainWindow::on_pushButton_18_clicked(){ dialog13->exec(); }
void MainWindow::on_pushButton_19_clicked(){ dialog21->exec(); }
void MainWindow::on_pushButton_20_clicked(){ dialog22->exec(); }
void MainWindow::on_pushButton_21_clicked(){ dialog23->exec(); }
