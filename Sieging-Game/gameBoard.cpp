#include "gameBoard.h"

gameBoard::gameBoard(Game *gameInstance, QWidget *parent) : QWidget(parent), game(gameInstance)
{
    getSituation=0;
    gameOverDialogWindow = new gameOverDialog(this);

    loadImages(); // 加载图片

    // 设置为自适应大小
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding); // 允许 gameBoard 在父窗口中扩展
}

gameBoard::~gameBoard() = default;

void gameBoard::sleep(int time)
{
    this->setEnabled(false);
    QEventLoop loop;
    QTimer::singleShot(time, &loop, &QEventLoop::quit);
    loop.exec();  // 进入事件循环并等待 QTimer 完成
    this->setEnabled(true);

}
