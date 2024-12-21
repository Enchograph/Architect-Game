#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow),
      boardWidget(nullptr),                // 初始化 boardWidget
      gridDialog(new gridSizeDialog(this)) // 初始化 gridSizeDialog
{
    ui->setupUi(this);

    // 设置窗口大小为屏幕宽度的 70% 和高度的 70%
    QScreen *screen = QGuiApplication::primaryScreen();
    QRect screenGeometry = screen->geometry();
    this->resize(screenGeometry.width() * 0.7, screenGeometry.height() * 0.7);

    // 设置默认显示的页面为 beginPage
    ui->contentPage->setCurrentWidget(ui->beginPage);

    ui->passwordInput->setEchoMode(QLineEdit::Password);
    ui->newPasswordInput->setEchoMode(QLineEdit::Password);

    setupConnections();

    currentUser = nullptr;

    QPixmap defaultPixmap(":/resources/DefaultAvatar.png");

    ui->avatarLabel->setPixmap(defaultPixmap);

    QMovie *vsComptrMovie = new QMovie(":/resources/vsComptr.gif", QByteArray(), this);
    QMovie *vsPeopleMovie = new QMovie(":/resources/vsPeople.gif", QByteArray(), this);
    QMovie *loginMovie = new QMovie(":/resources/login.gif", QByteArray(), this);
    QMovie *settingMovie = new QMovie(":/resources/rule.gif", QByteArray(), this);
    QMovie *aboutMovie = new QMovie(":/resources/about.gif", QByteArray(), this);

    letGifBegin(vsComptrMovie, ui->vsComptrGifLabel);
    letGifBegin(vsPeopleMovie, ui->vsPeopleGifLabel);
    letGifBegin(loginMovie, ui->loginGifLabel);
    //    letGifBegin(settingMovie,ui->settingGifLabel);
    //    letGifBegin(aboutMovie,ui->aboutGifLabel);
    letGifBegin(settingMovie, ui->aboutGifLabel);

    letGifBegin(vsComptrMovie, ui->vsComptrGifLabel_2);
    letGifBegin(vsPeopleMovie, ui->vsPeopleGifLabel_2);
    letGifBegin(loginMovie, ui->loginGifLabel_2);

    dialog11 = new gridSizeDialog(this);
    dialog12 = new gridSizeDialog(this);
    dialog13 = new gridSizeDialog(this);
    dialog14 = new gridSizeDialog(this);
    dialog14->setValue(5);
    dialog21 = new gridSizeDialog(this);
    dialog21->setCheckBoxVisible(false);

    // 连接 gridSizeDialog 的 accepted 信号到游戏开始槽函数
    connect(dialog11, &gridSizeDialog::accepted, this, [this]()
            { openGamePage(dialog11, InitialState::human, Difficulty::simple); });
    connect(dialog12, &gridSizeDialog::accepted, this, [this]()
            { openGamePage(dialog12, InitialState::human, Difficulty::medium); });
    connect(dialog13, &gridSizeDialog::accepted, this, [this]()
            { openGamePage(dialog13, InitialState::human, Difficulty::hard); });
    connect(dialog14, &gridSizeDialog::accepted, this, [this]()
            { openGamePage(dialog14, InitialState::human, Difficulty::hard); });
    connect(dialog21, &gridSizeDialog::accepted, this, [this]()
            { openGamePage(dialog21, InitialState::player1, Difficulty::medium); });

    // 初始化 gamePage，俟其后添加 gameBoard
    ui->gamePage->setLayout(new QVBoxLayout);
}

MainWindow::~MainWindow()
{
    delete ui;
}
