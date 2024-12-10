#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QScreen>
#include <QGuiApplication>
#include <QStackedWidget>
#include <QPropertyAnimation>
#include "gridSizeDialog.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // 获取主屏幕的尺寸
    QScreen *screen = QGuiApplication::primaryScreen();
    QRect screenGeometry = screen->geometry();
    int screenWidth = screenGeometry.width();
    int screenHeight = screenGeometry.height();

    // 设置窗口大小为屏幕宽度的 70% 和高度的 70%
    int windowWidth = screenWidth * 0.7;
    int windowHeight = screenHeight * 0.7;
    this->resize(windowWidth, windowHeight);

    // 设置默认显示的页面为 beginPage
    ui->contentPage->setCurrentWidget(ui->beginPage);
}

MainWindow::~MainWindow()
{
    delete ui;
}

// 点击按钮后切换到人机对弈页面
void MainWindow::on_vsAiBtn_clicked()
{
    if (ui->contentPage->currentWidget() != ui->vsAiPage) {
        switchPageWithAnimation(ui->vsAiPage);
    }
}

// 点击按钮后切换到双人游戏页面
void MainWindow::on_vsPeopleBtn_clicked()
{
    if (ui->contentPage->currentWidget() != ui->vsPeoplePage) {
        switchPageWithAnimation(ui->vsPeoplePage);
    }
}

// 点击按钮后切换到首页
void MainWindow::on_mainPageBtn_clicked()
{
    if (ui->contentPage->currentWidget() != ui->beginPage) {
        switchPageWithAnimation(ui->beginPage);
    }
}

// 点击按钮后切换到登录页面
void MainWindow::on_loginBtn_clicked()
{
    if (ui->contentPage->currentWidget() != ui->loginPage) {
        switchPageWithAnimation(ui->loginPage);
    }
}

// 点击按钮后切换到设置页面
void MainWindow::on_settingsBtn_clicked()
{
    if (ui->contentPage->currentWidget() != ui->settingPage) {
        switchPageWithAnimation(ui->settingPage);
    }
}

// 页面切换动画函数
void MainWindow::switchPageWithAnimation(QWidget *targetPage)
{
    QWidget *currentPage = ui->contentPage->currentWidget();
    int pageHeight = ui->contentPage->height();

    // 获取当前页面和目标页面的索引
    int currentIndex = getPageIndex(currentPage);
    int targetIndex = getPageIndex(targetPage);

    // 隐藏当前页面（向上滑动）
    QPropertyAnimation *hideAnim = new QPropertyAnimation(currentPage, "geometry", this);
    hideAnim->setDuration(500);
    hideAnim->setEasingCurve(QEasingCurve::InCubic); // 设置缓动曲线

    if (targetIndex > currentIndex) {
        // 向上滑动（目标页面在当前页面之后）
        hideAnim->setStartValue(currentPage->geometry());
        hideAnim->setEndValue(QRect(0, -pageHeight, currentPage->width(), currentPage->height()));
    } else {
        // 向下滑动（目标页面在当前页面之前）
        hideAnim->setStartValue(currentPage->geometry());
        hideAnim->setEndValue(QRect(0, pageHeight, currentPage->width(), currentPage->height()));
    }

    // 显示目标页面（从顶部滑入）
    QPropertyAnimation *showAnim = new QPropertyAnimation(targetPage, "geometry", this);
    showAnim->setDuration(500);
    showAnim->setEasingCurve(QEasingCurve::InCubic); // 设置缓动曲线

    if (targetIndex > currentIndex) {
        // 如果目标页面在当前页面之后，目标页面从底部滑入
        showAnim->setStartValue(QRect(0, pageHeight, targetPage->width(), targetPage->height()));
    } else {
        // 如果目标页面在当前页面之前，目标页面从顶部滑入
        showAnim->setStartValue(QRect(0, -pageHeight, targetPage->width(), targetPage->height()));
    }

    showAnim->setEndValue(QRect(0, 0, targetPage->width(), targetPage->height()));

    // 切换页面逻辑
    connect(hideAnim, &QPropertyAnimation::finished, this, [=]() {
        ui->contentPage->setCurrentWidget(targetPage);
        showAnim->start(); // 开始显示动画
    });

    hideAnim->start(); // 开始隐藏动画
}


// 获取页面的索引
int MainWindow::getPageIndex(QWidget *page)
{
    if (page == ui->beginPage) {
        return 0;
    } else if (page == ui->vsAiPage) {
        return 1;
    } else if (page == ui->vsPeoplePage) {
        return 2;
    } else if (page == ui->loginPage) {
        return 3;
    } else if (page == ui->settingPage) {
        return 4;
    }
    return -1; // 如果页面不存在，返回-1
}

void MainWindow::on_pushButton_16_clicked()
{
    gridSizeDialog *dialog;
    dialog = new gridSizeDialog(this); // 创建对话框
    dialog->exec(); // 显示对话框并等待用户操作
}
