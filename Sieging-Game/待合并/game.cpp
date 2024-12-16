#include "game.h"


Cell::Cell(Edge *topE, Edge *leftE, Edge *rightE, Edge *bottomE, int x1, int y1)
{
    topEdge = topE;
    leftEdge = leftE;
    rightEdge = rightE;
    bottomEdge = bottomE;
    x = x1;
    y = y1;
}

Cell::Cell() { color = white; }

bool Cell::check(Color player)
{
    if (topEdge->isSelected && leftEdge->isSelected && rightEdge->isSelected && bottomEdge->isSelected)
    {
        color = player;
        // 再加一个给方格组件染色/改背景图片的步骤。
        return true;
    }
    return false;
}

Edge *Cell::unselectedEdgesLeft()
{
    int count = 0;
    if (topEdge->isSelected)
        count++;
    if (leftEdge->isSelected)
        count++;
    if (rightEdge->isSelected)
        count++;
    if (bottomEdge->isSelected)
        count++;
    if (count != 3)
    {
        return NULL;
    }
    else
    {
        if (!(topEdge->isSelected))
            return topEdge;
        if (!(leftEdge->isSelected))
            return leftEdge;
        if (!(rightEdge->isSelected))
            return rightEdge;
        if (!(bottomEdge->isSelected))
            return bottomEdge;
    }
}

Game::Game(int width1, int height1, Mode playMode1, Difficulty difficulty1)
{
    width = width1;
    height = height1;
    playMode = playMode1;
    difficulty=difficulty1;
    playerNow = blue;
    cellSituation.resize(height - 1, std::vector<Cell>(width - 1));
    edgeSituation.resize(2 * height - 1, std::vector<Edge>(width));

    for (int x1 = 0; x1 < 2 * height1 - 1; x1++) // 边初始化
    {
        if (x1 % 2 == 0) // 横线
        {
            for (int y1 = 0; y1 < width1 - 1; y1++)
            {
                edgeSituation[x1][y1].x = x1;
                edgeSituation[x1][y1].y = y1;
            }
        }
        if (x1 % 2 == 1) // 竖线
        {
            for (int y1 = 0; y1 < width1; y1++)
            {
                edgeSituation[x1][y1].x = x1;
                edgeSituation[x1][y1].y = y1;
            }
        }
    }

    for (int x1 = 0; x1 < height1 - 1; x1++) // 格初始化
    {
        for (int y1 = 0; y1 < width1 - 1; y1++)
        {
            cellSituation[x1][y1].x = x1;
            cellSituation[x1][y1].y = y1;
            cellSituation[x1][y1].topEdge = &edgeSituation[2 * x1][y1];
            cellSituation[x1][y1].leftEdge = &edgeSituation[2 * x1 + 1][y1];
            cellSituation[x1][y1].rightEdge = &edgeSituation[2 * x1 + 1][y1 + 1];
            cellSituation[x1][y1].bottomEdge = &edgeSituation[2 * x1 + 2][y1];
        }
    }
}

void Game::selectEdge(int x, int y, Color player)
{
    edgeSituation[x][y].isSelected = true;
    // 这里再插一个边变色代码
    checkCell(x,y,player);



}
void Game::nextTurn()
{
    if(getMode()==vsComptr)
    {
        if(getPlayer()==blue)
        {
            setPlayer(orange);
        }
        else if(getPlayer()==orange)
        {
            setPlayer(blue);
        }
        //这里需要加一个判断下一步是ai还是人类的步骤。
        selectEdge(aiLogic(getDifficulty())->x,aiLogic(getDifficulty())->y,getPlayer());
    }
    else if(getMode()==vsHuman)
    {
        if(getPlayer()==blue)
        {
            setPlayer(orange);
        }
        else if(getPlayer()==orange)
        {
            setPlayer(blue);
        }
    }
}



void Game::checkCell(int x, int y, Color player)
{
    if (x % 2 == 0) // 横线
    {
        if (x == 0) // 最上方的一行，检查下面的方块
        {
            if (cellSituation[x / 2][y].check(player))
            {
                if (checkGameOver())
                {
                    gameOver();
                }
            }
        }
        else if (x / 2 - 1 == height - 2) // 最下方的一行，检查上面的方块
        {
            if (cellSituation[x / 2 - 1][y].check(player))
            {
                if (checkGameOver())
                {
                    gameOver();
                }
            }
        }
        else // 中间的行，两边都检查
        {
            if (cellSituation[x / 2][y].check(player))
            {
                if (checkGameOver())
                {
                    gameOver();
                }
            }
            if (cellSituation[x / 2 - 1][y].check(player))
            {
                if (checkGameOver())
                {
                    gameOver();
                }
            }
        }
    }
    if (x % 2 == 1) // 竖线
    {
        if (y == 0) // 最左端的一行，检查右边的方块
        {
            if (cellSituation[(x - 1) / 2][y].check(player))
            {
                if (checkGameOver())
                {
                    gameOver();
                }
            }
        }
        else if (y == width - 1) // 最右端的一行，检查左边的方块
        {
            if (cellSituation[(x - 1) / 2][y - 1].check(player))
            {
                if (checkGameOver())
                {
                    gameOver();
                }
            }
        }
        else
        {
            if (cellSituation[(x - 1) / 2][y].check(player))
            {
                if (checkGameOver())
                {
                    gameOver();
                }
            }
            if (cellSituation[(x - 1) / 2][y - 1].check(player))
            {
                if (checkGameOver())
                {
                    gameOver();
                }
            }
        }
    }
}

bool Game::checkGameOver()
{
    for (int x1 = 0; x1 < height - 1; x1++) // 遍历每一格
    {
        for (int y1 = 0; y1 < width - 1; y1++)
        {
            if (cellSituation[x1][y1].color == white)
                return false;
        }
    }
    return true;
}

int Game::countPlayerCells(Color player) const
{
    int count = 0;
    for (int x1 = 0; x1 < height - 1; x1++) // 遍历每一格
    {
        for (int y1 = 0; y1 < width - 1; y1++)
        {
            if (cellSituation[x1][y1].color == player)
                count++;
        }
    }
    return count;
}

void Game::gameOver()
{
    if (countPlayerCells(blue) > countPlayerCells(orange))
    {
        // 蓝方胜逻辑
    }
    else if (countPlayerCells(blue) > countPlayerCells(orange))
    {
        // 橙方胜逻辑
    }
    else
    {
        // 平局逻辑
    }
}

void Game::reset()
    {

        cellSituation.resize(height - 1, std::vector<Cell>(width - 1));
        edgeSituation.resize(2 * height - 1, std::vector<Edge>(width));
        for (int x1 = 0; x1 < 2 * height - 1; x1++) // 边初始化
        {
            if (x1 % 2 == 0) // 横线
            {
                for (int y1 = 0; y1 < width - 1; y1++)
                {
                    edgeSituation[x1][y1].x = x1;
                    edgeSituation[x1][y1].y = y1;
                }
            }
            if (x1 % 2 == 1) // 竖线
            {
                for (int y1 = 0; y1 < width; y1++)
                {
                    edgeSituation[x1][y1].x = x1;
                    edgeSituation[x1][y1].y = y1;
                }
            }
        }
        for (int x1 = 0; x1 < height - 1; x1++) // 格初始化
        {
            for (int y1 = 0; y1 < width - 1; y1++)
            {
                cellSituation[x1][y1].x = x1;
                cellSituation[x1][y1].y = y1;
                cellSituation[x1][y1].topEdge = &edgeSituation[2 * x1][y1];
                cellSituation[x1][y1].leftEdge = &edgeSituation[2 * x1 + 1][y1];
                cellSituation[x1][y1].rightEdge = &edgeSituation[2 * x1 + 1][y1 + 1];
                cellSituation[x1][y1].bottomEdge = &edgeSituation[2 * x1 + 2][y1];
            }
        }
    }

Edge * Game::aiLogic(Difficulty a)
{
    switch(a)
    {
        case simple:
            return simpleAiLogic();
        break;
        case medium:
            return mediumAiLogic();
        break;
    case hard:
        return hardAiLogic();
        break;
    default:
        return simpleAiLogic();
    }
}

Edge * Game::simpleAiLogic()
{
    srand(static_cast<unsigned int>(time(0))); // 设置随机数种子
    int randomX, randomY;
    for (int z = 0; z < 10; z++)
    {
        if (rand() % 2 == 0)
        {
            randomX = rand() % height;
            randomX *= 2;
            randomY = rand() % (width - 1);
            if (edgeSituation[randomX][randomY].isSelected == false)
            {
                return &edgeSituation[randomX][randomY];
            }
        }
        else
        {
            randomX = rand() % (height - 1);
            randomX = randomX * 2 + 1;
            randomY = rand() % width;
            if (edgeSituation[randomX][randomY].isSelected == false)
            {
                return &edgeSituation[randomX][randomY];
            }
        }
    }
    for (int x1 = 0; x1 < 2 * height - 1; x1++) // 太非了就遍历每一条边
    {
        if (x1 % 2 == 0) // 横线
        {
            for (int y1 = 0; y1 < width - 1; y1++)
            {
                if (edgeSituation[randomX][randomY].isSelected == false)
                {
                    return &edgeSituation[randomX][randomY];
                }
            }
        }
        if (x1 % 2 == 1) // 竖线
        {
            for (int y1 = 0; y1 < width; y1++)
            {
                if (edgeSituation[randomX][randomY].isSelected == false)
                {
                    return &edgeSituation[randomX][randomY];
                }
            }
        }
    }
}

Edge * Game::mediumAiLogic()
{
    for (int x1 = 0; x1 < height - 1; x1++) // 先遍历每一格找局部最优解
    {
        for (int y1 = 0; y1 < width - 1; y1++)
        {
            if (cellSituation[x1][y1].unselectedEdgesLeft() != NULL)
            {
                return cellSituation[x1][y1].unselectedEdgesLeft();
            }
        }
    }
    // 找不到就随机
    srand(static_cast<unsigned int>(time(0))); // 设置随机数种子
    int randomX, randomY;
    for (int z = 0; z < 10; z++)
    {
        if (rand() % 2 == 0)
        {
            randomX = rand() % height;
            randomX *= 2;
            randomY = rand() % (width - 1);
            if (edgeSituation[randomX][randomY].isSelected == false)
            {
                return &edgeSituation[randomX][randomY];
            }
        }
        else
        {
            randomX = rand() % (height - 1);
            randomX = randomX * 2 + 1;
            randomY = rand() % width;
            if (edgeSituation[randomX][randomY].isSelected == false)
            {
                return &edgeSituation[randomX][randomY];
            }
        }
    }
    for (int x1 = 0; x1 < 2 * height - 1; x1++) // 太非了就遍历每一条边
    {
        if (x1 % 2 == 0) // 横线
        {
            for (int y1 = 0; y1 < width - 1; y1++)
            {
                if (edgeSituation[randomX][randomY].isSelected == false)
                {
                    return &edgeSituation[randomX][randomY];
                }
            }
        }
        if (x1 % 2 == 1) // 竖线
        {
            for (int y1 = 0; y1 < width; y1++)
            {
                if (edgeSituation[randomX][randomY].isSelected == false)
                {
                    return &edgeSituation[randomX][randomY];
                }
            }
        }
    }
}

Edge * Game::hardAiLogic()
{
}

// 行棋逻辑
