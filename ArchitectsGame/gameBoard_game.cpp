#include "gameBoard.h"

void gameBoard::mousePressEvent(QMouseEvent *event)
{

    int y = ceil(event->y() / (5 * size) - 0.1); // 根据点击的 Y 坐标确定行
    int x = ceil(event->x() / (5 * size) - 0.1); // 根据点击的 X 坐标确定列
    // 暂时还不清楚这里用向上取整反而能跑通的原因，稍后详加分析。

    if (x < 0 || y < 0 || x >= game->getWidth() || y >= game->getHeight())
        return;

    if (selectEdgeByClicking(x, y, event).x == -213)
        return;

    update(); // 更新界面

    if (!game->checkGameOver())
    {
        nextStepFuction();
    }
    else
    {
        endAndSettlement();
    }
    update();
}

Edge gameBoard::selectEdgeByClicking(int x, int y, QMouseEvent *event)
{
    Edge a;
    a.color = white;
    a.turnsAfterSelected = 0;

    double manhattanDistance1 = abs(3 * size + 5 * x * size - event->x()) + abs(0.5 * size + 5 * y * size - event->y());
    double manhattanDistance4 = abs(3 * size + 5 * x * size - event->x()) + abs(0.5 * size + 5 * size + 5 * y * size - event->y());
    double manhattanDistance2 = abs(3 * size + 5 * y * size - event->y()) + abs(0.5 * size + 5 * x * size - event->x());
    double manhattanDistance3 = abs(3 * size + 5 * y * size - event->y()) + abs(0.5 * size + 5 * x * size + 5 * x - event->x());

    int resX, resY;
    if (manhattanDistance1 <= size) // 依原意这里的 size 应该乘四才对。不过现在的效果也可以，就不改了。
    {
        resX = 2 * y;
        resY = x;
        qDebug() << "上边";
    }
    else if (manhattanDistance2 <= size)
    {
        resX = y * 2 + 1;
        resY = x;
        qDebug() << "左边";
    }
    else if (manhattanDistance3 <= size)
    {
        resX = y * 2 + 1;
        resY = x + 1;
        qDebug() << "右边";
    }
    else if (manhattanDistance4 <= size)
    {
        resX = y * 2 + 2;
        resY = x;
        qDebug() << "下边";
    }
    else
    {
        resX = -213;
        resY = -213;
        qDebug() << "计算曼哈顿距离时出错/超出点击范围";
    }
    if (resX != -213)
        if (game->getEdge(resX, resY).color != white)
        {
            resX = -213;
            resY = -213;
        }
    a.x = resX;
    a.y = resY;

    if (a.x != -213)
    {
        switch (game->getInitialState())
        {
        case comptr:
            game->selectEdge(resX, resY, orange);
            break;
        case human:
            game->selectEdge(resX, resY, blue);
            break;
        case player1:
            game->selectEdge(resX, resY, game->getPlayerNow());
            break;
        }
    }
    return a;
}

void gameBoard::nextStepFuction()
{

    if (!game->playerExtraTurn)
    {
        if (game->getInitialState() == comptr)
        {
            do
            {
                aiStep(blue);
            } while (game->playerExtraTurn && (!game->checkGameOver()));

            if (game->checkGameOver())
                endAndSettlement();
        }
        if (game->getInitialState() == human)
        {
            do
            {
                aiStep(orange);
            } while (game->playerExtraTurn && (!game->checkGameOver()));
            if (game->checkGameOver())
                endAndSettlement();
        }
        if (game->getInitialState() == player1)
        {
            if (game->getPlayerNow() == blue)
            {
                game->setPlayer(orange);
            }
            else
            {
                game->setPlayer(blue);
            }
        }
    }
}

void gameBoard::aiStep(Color color)
{
    sleep(aiThinkingTime);

    Edge *nextStep = game->aiLogic(game->getDifficulty());
    int x = nextStep->x;
    int y = nextStep->y;
    game->selectEdge(x, y, color);

    update(); // 更新界面
}

void gameBoard::endAndSettlement()
{
    if (game->getInitialState() == comptr)
    {
        if (game->gameOver() == 2)
        {

            getSituation = 3;
            gameOverDialogWindow->setDialogText("\n蓝方获胜！\n\n您可以在账户信息里\n查看自己的对局记录。");
            gameOverDialogWindow->exec();
        }
        else if (game->gameOver() == 3)
        {

            getSituation = 2;
            gameOverDialogWindow->setDialogText("\n橙方获胜！\n\n您可以在账户信息里\n查看自己的对局记录。");
            gameOverDialogWindow->exec();
        }
        else if (game->gameOver() == 1)
        {

            getSituation = 1;

            gameOverDialogWindow->setDialogText("\n平局\n\n您可以在账户信息里\n查看自己的对局记录。");
            gameOverDialogWindow->exec();
        }
    }
    if (game->getInitialState() == human)
    {
        if (game->gameOver() == 2)
        {

            getSituation = 2;
            gameOverDialogWindow->setDialogText("\n蓝方获胜！\n\n您可以在账户信息里\n查看自己的对局记录。");
            gameOverDialogWindow->exec();
        }
        else if (game->gameOver() == 3)
        {

            getSituation = 3;
            gameOverDialogWindow->setDialogText("\n橙方获胜！\n\n您可以在账户信息里\n查看自己的对局记录。");
            gameOverDialogWindow->exec();
        }
        else if (game->gameOver() == 1)
        {

            getSituation = 1;
            gameOverDialogWindow->setDialogText("\n平局。\n\n您可以在账户信息里\n查看自己的对局记录。");
            gameOverDialogWindow->exec();
        }
    }
    if (game->getInitialState() == player1)
    {
        if (game->gameOver() == 2)
        {
            getSituation = 4;

            gameOverDialogWindow->setDialogText("\n蓝方获胜！\n                  ");
            gameOverDialogWindow->exec();
        }
        else if (game->gameOver() == 3)
        {

            getSituation = 4;
            gameOverDialogWindow->setDialogText("\n橙方获胜！\n                  ");
            gameOverDialogWindow->exec();
        }
        else if (game->gameOver() == 1)
        {

            getSituation = 4;
            gameOverDialogWindow->setDialogText("\n平局。\n                  ");
            gameOverDialogWindow->exec();
        }
    }
}
