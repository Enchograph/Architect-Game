#include "mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::openGamePage(const gridSizeDialog * gridDialog,InitialState initialState,Difficulty difficulty)
{
    int gridSize = gridDialog->getGridSize(); // 获取用户选择的棋盘大小
    bool robotFirst = gridDialog->getFirstHand();

    // 如果已经存在 gameBoard，先删除它（避免重复初始化）
    if (boardWidget) {
        delete boardWidget;
        boardWidget = nullptr;
    }

    if(robotFirst&&initialState!=player1)
    {
        boardWidget = new gameBoard(new Game(gridSize,gridSize,comptr,difficulty), this);

    }
    else
    {
        boardWidget = new gameBoard(new Game(gridSize,gridSize,initialState,difficulty), this);

    }

    // 将 gameBoard 添加到 gamePage 的布局中
    ui->gamePage->layout()->addWidget(boardWidget);

    // 切换到 gamePage
    ui->contentPage->setCurrentWidget(ui->gamePage);


    connect(boardWidget->gameOverDialogWindow, &gameOverDialog::dialogClosed, this, &MainWindow::onGameOverDialogClosed);


}

void MainWindow::onGameOverDialogClosed()
{
    if(currentUser)
    {
    qDebug()<<"onGameOverDialogClosed()";
    qDebug()<<boardWidget->getSituation;
        switch (boardWidget->getSituation) {
        case 1:
            currentUser->currentDrawNum++;
            break;
        case 2:
            currentUser->currentWinNum++;
             break;
        case 3:
            currentUser->currentLoseNum++;
              break;
        default:
              break;
    }
updateUserInformation();
UserManager::storageUserInformation(currentUser);




    }
}


void MainWindow::onEndGameButtonClicked()
{
    onGameOverDialogClosed();
    qDebug()<<"onEndGameButtonClicked()";

}

