#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPropertyAnimation>


#include "game.h"
#include "gameBoard.h"
#include "gridSizeDialog.h"
#include "cropWindow.h"
#include "userManager.h"

#include <QScreen>
#include <QGuiApplication>
#include <QStackedWidget>

#include <QMessageBox>
#include <QMovie>

#include <QDebug>

#include <QFileDialog>
#include <QPixmap>

#include <QThread>

#include <QStandardPaths>




QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_vsComptrBtn_clicked();
    void on_vsPeopleBtn_clicked();
    void on_mainPageBtn_clicked();
    void on_loginBtn_clicked();
    void on_settingsBtn_clicked();
    void on_aboutBtn_clicked();
    void on_vsComptrBtn_2_clicked();
    void on_vsPeopleBtn_2_clicked();
    void on_mainPageBtn_2_clicked();
    void on_loginBtn_2_clicked();
    void on_settingsBtn_2_clicked();
    void on_aboutBtn_2_clicked();
    void on_ruleBtn_clicked();
    void on_ruleBtn_2_clicked();
    void on_pushButton_16_clicked();
    void on_pushButton_17_clicked();
    void on_pushButton_18_clicked();
    void on_pushButton_19_clicked();
    void on_pushCowButton_clicked();
    void on_selectAvatarBtn_clicked();       // 按钮点击槽函数
    void onImageCropped(const QPixmap &croppedPixmap);  // 裁剪完成槽函数
    void onEndGameButtonClicked(); // 结束游戏按钮点击事件
    void onGameOverDialogClosed(); // 游戏结束对话框关闭时的操作

private:
    Ui::MainWindow *ui;
    void switchPage(QWidget *targetPage); // 页面切换函数
    int getPageIndex(QWidget *page); // 获取页面的索引
    void updatePageLayout(int pageIndex);



    Game *game;
    gameBoard *board;

    gameBoard *boardWidget;     // gameBoard 实例
    gridSizeDialog *gridDialog; // gridSizeDialog 实例

    void openGamePage(const gridSizeDialog * gridDialog,InitialState initialState,Difficulty difficulty); // 处理开始游戏逻辑

    gridSizeDialog * dialog11;
    gridSizeDialog * dialog12;
    gridSizeDialog * dialog13;
    gridSizeDialog * dialog14;
    gridSizeDialog * dialog21;
    gridSizeDialog * dialog22;
    gridSizeDialog * dialog23;

   UserInformation * currentUser;
   UserInformation acturalCurrentUser;







   void goToAccountPage();

        void setupConnections();

        void updateUserInformation();




        void adjustGifSize(QMovie *movie,QLabel * gifLabel) ;
            //void resizeEvent(QResizeEvent *event) ;
                void letGifBegin(QMovie *movie,QLabel * gifLabel);
                void resizeGif(QLabel * gifLabel);



};

#endif // MAINWINDOW_H
