#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPropertyAnimation>

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

#include "game.h"
#include "gameBoard.h"
#include "gridSizeDialog.h"
#include "cropWindow.h"
#include "userManager.h"

QT_BEGIN_NAMESPACE
namespace Ui
{
    class MainWindow;
}
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

    // 游戏开始按钮
    void on_pushButton_16_clicked();
    void on_pushButton_17_clicked();
    void on_pushButton_18_clicked();
    void on_pushButton_19_clicked();
    void on_pushCowButton_clicked();

    // 上传头像相关按钮
    void on_selectAvatarBtn_clicked();
    void onImageCropped(const QPixmap &croppedPixmap);

    // 游戏结算对话框相关按钮
    void onEndGameButtonClicked();
    void onGameOverDialogClosed();

private:
    Ui::MainWindow *ui;

    void switchPage(QWidget *targetPage);
    int getPageIndex(QWidget *page);
    void updatePageLayout(int pageIndex);

    Game *game;
    gameBoard *board; // 这个应该没用了

    gameBoard *boardWidget;
    gridSizeDialog *gridDialog;

    UserInformation *currentUser;
    UserInformation acturalCurrentUser;

    gridSizeDialog *dialog11;
    gridSizeDialog *dialog12;
    gridSizeDialog *dialog13;
    gridSizeDialog *dialog14;
    gridSizeDialog *dialog21;
    gridSizeDialog *dialog22;
    gridSizeDialog *dialog23;

    void openGamePage(const gridSizeDialog *gridDialog, InitialState initialState, Difficulty difficulty); // 处理开始游戏逻辑

    void goToAccountPage(); // 去空用户页和去实际用户页的选择

    void setupConnections();

    void updateUserInformation();

    void adjustGifSize(QMovie *movie, QLabel *gifLabel);
    void letGifBegin(QMovie *movie, QLabel *gifLabel);
    void resizeGif(QLabel *gifLabel);
};

#endif // MAINWINDOW_H
