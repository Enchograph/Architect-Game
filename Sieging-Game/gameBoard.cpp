#include "gameBoard.h"

gameBoard::gameBoard(Game *gameInstance, QWidget *parent) : QWidget(parent), game(gameInstance)
{
    getSituation = 0;
    gameOverDialogWindow = new gameOverDialog(this);

    loadImages();

    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
}

gameBoard::~gameBoard() = default;

void gameBoard::sleep(int time)
{
    this->setEnabled(false);
    QEventLoop loop;
    QTimer::singleShot(time, &loop, &QEventLoop::quit);
    loop.exec();
    this->setEnabled(true);
}
