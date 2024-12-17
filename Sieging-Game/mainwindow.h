#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPropertyAnimation>
#include "game.h"
#include "gameBoard.h"
#include "gridSizeDialog.h"

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
    void on_pushButton_16_clicked();
    void on_pushButton_17_clicked();
    void on_pushButton_18_clicked();
    void on_pushButton_19_clicked();
    void on_pushButton_20_clicked();
    void on_pushButton_21_clicked();

private:
    Ui::MainWindow *ui;
    void switchPage(QWidget *targetPage); // 页面切换函数
    int getPageIndex(QWidget *page); // 获取页面的索引

    Game *game;
    gameBoard *board;

    gameBoard *boardWidget;     // gameBoard 实例
    gridSizeDialog *gridDialog; // gridSizeDialog 实例

    void openGamePage(const gridSizeDialog * gridDialog,InitialState initialState,Difficulty difficulty); // 处理开始游戏逻辑

    gridSizeDialog * dialog11;
    gridSizeDialog * dialog12;
    gridSizeDialog * dialog13;
    gridSizeDialog * dialog21;
    gridSizeDialog * dialog22;
    gridSizeDialog * dialog23;

};

#endif // MAINWINDOW_H
