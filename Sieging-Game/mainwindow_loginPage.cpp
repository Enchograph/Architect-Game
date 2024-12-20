#include "mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::updateUserInformation()
{
    ui->accountInfoLabel->setText("用户名：" + currentUser->currentUserName +
                                  "\nUID：" + currentUser->currentUid +
                                  "\n胜利场数：" + QString::number(currentUser->currentWinNum) +
                                  "\n失败场数：" + QString::number(currentUser->currentLoseNum) +
                                  "\n平局次数：" + QString::number(currentUser->currentDrawNum));
    ui->userNameLabel->setText("用户名：" + currentUser->currentUserName);
    ui->UIDLabel->setText("UID：" + currentUser->currentUid);

    QString filePath = currentUser->currentUid + ".png";

        if (!filePath.isEmpty())
        {
            // 加载图片并显示到 QLabel
            QPixmap pixmap(filePath);
            QPixmap defaultPixmap(":/resources/DefaultAvatar.png");


            if (!pixmap.isNull())
            {
                ui->avatarLabel->setPixmap(pixmap);
                ui->userAvatarAtInfPageLabel->setPixmap(pixmap);
            }
            else
            {
                ui->avatarLabel->setPixmap(defaultPixmap);
                ui->userAvatarAtInfPageLabel->setPixmap(defaultPixmap);
            }
        }
}


void MainWindow::goToAccountPage()
{
    if (currentUser) {

        updateUserInformation();

        ui->stackedWidget->setCurrentWidget(ui->accountSettingsPage);
    } else {
        ui->stackedWidget->setCurrentWidget(ui->accountSettingsPage_2);
    }
}



void MainWindow::setupConnections() {
    // 页面切换逻辑
    connect(ui->loginButton, &QPushButton::clicked, [&]() {
        ui->stackedWidget->setCurrentWidget(ui->innerLoginPage);
    });

    connect(ui->registerButton, &QPushButton::clicked, [&]() {
        ui->stackedWidget->setCurrentWidget(ui->registerPage);
    });

    connect(ui->accountSettingsButton, &QPushButton::clicked, [&]() {
        goToAccountPage();
    });

    // 返回账户页面
    connect(ui->backToMenuButtonFromLogin, &QPushButton::clicked, [&]() {
        ui->stackedWidget->setCurrentWidget(ui->mainMenuPage);
    });

    connect(ui->backToMenuButtonFromRegister, &QPushButton::clicked, [&]() {
        ui->stackedWidget->setCurrentWidget(ui->mainMenuPage);
    });

    connect(ui->backToMenuButtonFromAccount, &QPushButton::clicked, [&]() {
        ui->stackedWidget->setCurrentWidget(ui->mainMenuPage);
    });

    connect(ui->backToMenuButtonFromAccount_2, &QPushButton::clicked, [&]() {
        ui->stackedWidget->setCurrentWidget(ui->mainMenuPage);
    });

    // 注册功能
    connect(ui->confirmRegisterButton, &QPushButton::clicked, [&]() {
        QString username = ui->newUsernameInput->text();
        QString password = ui->newPasswordInput->text();

        if (username.isEmpty() || password.isEmpty()) {
            QMessageBox::warning(this, "注册", "请填写所有输入框。");
            return;
        }

        if (UserManager::isUsernameTaken(username)) {
            QMessageBox::warning(this, "注册", "用户名已存在！");
            return;
        }

        UserManager::registerUser(username, password);
        QMessageBox::information(this, "注册", "注册成功！");
        ui->stackedWidget->setCurrentWidget(ui->mainMenuPage);
    });

    // 登录功能
    connect(ui->confirmLoginButton, &QPushButton::clicked, [&]() {
        QString username = ui->usernameInput->text();
        QString password = ui->passwordInput->text();

        currentUser = &acturalCurrentUser;
        bool loginSuccessfully = UserManager::loginUser(username, password,currentUser);

        if(loginSuccessfully)
        {
                        QMessageBox::information(this, "登录", "登录成功！");
                       updateUserInformation();
                                                goToAccountPage();
        }
        else {
                    QMessageBox::warning(this, "登录", "账号或密码不正确。");
                    currentUser=nullptr;
                }


    });

}
