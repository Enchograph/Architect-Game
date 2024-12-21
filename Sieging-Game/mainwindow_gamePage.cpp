#include "mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::openGamePage(const gridSizeDialog *gridDialog, InitialState initialState, Difficulty difficulty)
{
    int gridSize = gridDialog->getGridSize(); // 获取用户选择的棋盘大小
    bool robotFirst = gridDialog->getFirstHand();

    // 检查是否有已存在的 gameBoard 。若存在则删除以避免重复初始化。
    if (boardWidget)
    {
        delete boardWidget;
        boardWidget = nullptr;
    }

    if (robotFirst && initialState != player1)
    {
        boardWidget = new gameBoard(new Game(gridSize, gridSize, comptr, difficulty), this);
    }
    else
    {
        boardWidget = new gameBoard(new Game(gridSize, gridSize, initialState, difficulty), this);
    }

    // 添加棋盘至 gamePage 并切换至此。
    ui->gamePage->layout()->addWidget(boardWidget);
    ui->contentPage->setCurrentWidget(ui->gamePage);

    connect(boardWidget->gameOverDialogWindow, &gameOverDialog::dialogClosed, this, &MainWindow::onGameOverDialogClosed);
}

void MainWindow::onGameOverDialogClosed()
{
    if (currentUser)
    {
        qDebug() << "onGameOverDialogClosed()";
        qDebug() << boardWidget->getSituation;
        switch (boardWidget->getSituation)
        {
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
    qDebug() << "onEndGameButtonClicked()";
}
