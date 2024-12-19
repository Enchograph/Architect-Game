#include "mainwindow.h"
#include "ui_mainwindow.h"


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

    setupConnections();

    currentUser=NULL;

    QPixmap defaultPixmap(":/new/prefix1/resources/DefaultAvatar.png");

    ui->avatarLabel->setPixmap(defaultPixmap);


    //    QMovie *preservationMovie = new QMovie(":/new/prefix1/resources/Preservation.gif");

    //    QSize si(ui->preservationLabel->width(),ui->preservationLabel->height());
    //    preservationMovie->setScaledSize(si);

    //        ui->preservationLabel->setMovie(preservationMovie);
    //        preservationMovie->start();

        QPixmap *preservationMovie = new QPixmap(":/new/prefix1/resources/Preservation.png");
            QSize si(ui->preservationLabel->width(),ui->preservationLabel->height());
            * preservationMovie=preservationMovie->scaled(si);

            ui->preservationLabel->setPixmap(*preservationMovie);


    // 设置默认显示的页面为 beginPage
    ui->contentPage->setCurrentWidget(ui->beginPage);

    dialog11 = new gridSizeDialog(this);
    dialog12 = new gridSizeDialog(this);
    dialog13 = new gridSizeDialog(this);
    dialog21 = new gridSizeDialog(this);
    dialog21->setCheckBoxVisible(false);

    // 连接 gridSizeDialog 的 accepted 信号到自定义槽函数
    connect(dialog11, &gridSizeDialog::accepted, this, [this]() { openGamePage(dialog11 ,InitialState::human, Difficulty::simple); });
    connect(dialog12, &gridSizeDialog::accepted, this, [this]() { openGamePage(dialog12 ,InitialState::human, Difficulty::medium); });
    connect(dialog13, &gridSizeDialog::accepted, this, [this]() { openGamePage(dialog13 ,InitialState::human, Difficulty::hard); });
    connect(dialog21, &gridSizeDialog::accepted, this, [this]() { openGamePage(dialog21 ,InitialState::player1, Difficulty::medium); });

   // connect(ui->selectAvatarBtn, &QPushButton::clicked, this, &MainWindow::on_selectAvatarBtn_clicked);



       // 初始化 gamePage，后续添加 gameBoard
       ui->gamePage->setLayout(new QVBoxLayout);



}

MainWindow::~MainWindow()
{
    delete ui;
}






