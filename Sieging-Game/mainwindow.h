#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPropertyAnimation>

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
    void on_vsAiBtn_clicked();
    void on_vsPeopleBtn_clicked();
    void on_mainPageBtn_clicked();
    void on_loginBtn_clicked();
    void on_settingsBtn_clicked();

    void on_pushButton_16_clicked();

private:
    Ui::MainWindow *ui;
    void switchPageWithAnimation(QWidget *targetPage); // 页面切换动画函数
    int getPageIndex(QWidget *page); // 获取页面的索引
};

#endif // MAINWINDOW_H
