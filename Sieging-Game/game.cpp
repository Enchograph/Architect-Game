#include "game.h"

#include <iostream>

using std::cout;
using std::endl;

Game::Game(int width1, int height1, InitialState initialState1, Difficulty difficulty1)
{
    width = width1;
    height = height1;

    initialState = initialState1;
    difficulty = difficulty1;
    playerNow = blue;
    playerExtraTurn = false;

    cellSituation.resize(height - 1, std::vector<Cell>(width - 1));
    edgeSituation.resize(2 * height - 1, std::vector<Edge>(width));

    for (int x1 = 0; x1 < 2 * height1 - 1; x1++) // �߳�ʼ��
    {
        if (x1 % 2 == 0) // ����
        {
            for (int y1 = 0; y1 < width1 - 1; y1++)
            {
                edgeSituation[x1][y1].x = x1;
                edgeSituation[x1][y1].y = y1;
            }
        }
        if (x1 % 2 == 1) // ����
        {
            for (int y1 = 0; y1 < width1; y1++)
            {
                edgeSituation[x1][y1].x = x1;
                edgeSituation[x1][y1].y = y1;
            }
        }
    }

    for (int x1 = 0; x1 < height1 - 1; x1++) // ���ʼ��
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

    if (getInitialState() == comptr)
    {
        Edge *nextStep = aiLogic(getDifficulty());
        int x = nextStep->x;
        int y = nextStep->y;
        selectEdge(x, y, getPlayerNow());
    }
}

void Game::selectEdge(int x, int y, Color player)
{
    edgeSituation[x][y].color = player;

    for (int x1 = 0; x1 < 2 * height - 1; x1++) // ����ÿһ����
    {
        if (x1 % 2 == 0) // ����
        {
            for (int y1 = 0; y1 < width - 1; y1++)
            {
                if (edgeSituation[x1][y1].color!=white)
                {
                    edgeSituation[x1][y1].turnsAfterSelected++;
                }
            }
        }
        if (x1 % 2 == 1) // ����
        {
            for (int y1 = 0; y1 < width; y1++)
            {
                if (edgeSituation[x1][y1].color!=white)
                {
                    edgeSituation[x1][y1].turnsAfterSelected++;
                }
            }
        }
    }

    checkCell(x, y, player);
}
/*
void Game::nextTurn()
{
    // ��һ���ǲ�����
    // selectEdge(aiLogic(getDifficulty())->x,aiLogic(getDifficulty())->y,getPlayerNow());

    if (checkGameOver() == false)
    {
        if (playerExtraTurn)
        {
            if (getInitialState() == human)
            {
                Edge *nextStep = aiLogic(getDifficulty());
                int x = nextStep->x;
                int y = nextStep->y;
                if (getPlayerNow() == orange)
                {
                    selectEdge(x, y, getPlayerNow());
                    nextTurn();
                    playerExtraTurn=false;
                    // !�ƺ���Ҫ��һ���ػ�����Ĳ���
                }
            }
            if (getInitialState() == comptr)
            {
                Edge *nextStep = aiLogic(getDifficulty());
                int x = nextStep->x;
                int y = nextStep->y;

                // ����֤�߼�
                if (getPlayerNow() == blue)
                {
                    selectEdge(x, y, blue);
                    //nextTurn();
                    playerExtraTurn=false;
                    // !�ƺ���Ҫ��һ���ػ�����Ĳ���
                }
                else if (getPlayerNow() == orange)
                {
                }

                // selectEdge(x, y, blue); // ! ע�⣡������߼���Ҫ�޸���
            }
            if (getInitialState() == player1)
            {
                // Do Nothing

                // if (getPlayerNow() == blue)
                // {
                //     setPlayer(orange);
                // }
                // else if (getPlayerNow() == orange)
                // {
                //     setPlayer(blue);
                // }
            }
        }
        else
        {
            if (getInitialState() == human)
            {
                Edge *nextStep = aiLogic(getDifficulty());
                int x = nextStep->x;
                int y = nextStep->y;
                if (getPlayerNow() == blue)
                {
                    setPlayer(orange);
                    selectEdge(x, y, getPlayerNow());
                }
                else if (getPlayerNow() == orange)
                {
                    setPlayer(blue);
                }
            }
            if (getInitialState() == comptr)
            {
                Edge *nextStep = aiLogic(getDifficulty());
                int x = nextStep->x;
                int y = nextStep->y;

//                if (getPlayerNow() == blue)
//                {
//                    setPlayer(orange);
//                }
//                else if (getPlayerNow() == orange)
//                {
//                    setPlayer(blue);
//                    selectEdge(x, y, getPlayerNow());
//                }
                selectEdge(x, y, blue); // ! ע�⣡������߼���Ҫ�޸���
            }
            if (getInitialState() == player1)
            {
                if (getPlayerNow() == blue)
                {
                    setPlayer(orange);
                }
                else if (getPlayerNow() == orange)
                {
                    setPlayer(blue);
                }
            }
        }
    }
}
*/
void Game::checkAndChange(int x, int y, Color player)
{
    if (cellSituation[x][y].check(player))
    {
        if (checkGameOver())
        {
            gameOver();
        }
        playerExtraTurn = true;
    }
}

void Game::checkCell(int x, int y, Color player)
{

    playerExtraTurn = false;
    if (x % 2 == 0) // ����
    {
        if (x == 0) // ���Ϸ���һ�У��������ķ���
        {
            checkAndChange(x / 2, y, player);
        }
        else if (x / 2 - 1 == height - 2) // ���·���һ�У��������ķ���
        {
            checkAndChange(x / 2 - 1, y, player);
        }
        else // �м���У����߶����
        {
            checkAndChange(x / 2, y, player);
            checkAndChange(x / 2 - 1, y, player);
        }
    }
    if (x % 2 == 1) // ����
    {
        if (y == 0) // ����˵�һ�У�����ұߵķ���
        {
            checkAndChange((x - 1) / 2, y, player);
        }
        else if (y == width - 1) // ���Ҷ˵�һ�У������ߵķ���
        {
            checkAndChange((x - 1) / 2, y - 1, player);
        }
        else
        {
            checkAndChange((x - 1) / 2, y, player);
            checkAndChange((x - 1) / 2, y - 1, player);
        }
    }
}

bool Game::checkGameOver()
{
    for (int x1 = 0; x1 < height - 1; x1++) // ����ÿһ��
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
    for (int x1 = 0; x1 < height - 1; x1++) // ����ÿһ��
    {
        for (int y1 = 0; y1 < width - 1; y1++)
        {
            if (cellSituation[x1][y1].color == player)
                count++;
        }
    }
    return count;
}

void Game::gameOver() // ! ������Ҫ������Ϸ�����߼�
{
    if (countPlayerCells(blue) > countPlayerCells(orange))
    {
        cout << "����ʤ����" << endl;
        // ����ʤ�߼�
    }
    else if (countPlayerCells(blue) < countPlayerCells(orange))
    {
        cout << "�ȷ�ʤ����" << endl;
        // �ȷ�ʤ�߼�
    }
    else
    {
        cout << "ƽ�֣�" << endl;
        // ƽ���߼�
    }
}

void Game::reset()
{

    cellSituation.resize(height - 1, std::vector<Cell>(width - 1));
    edgeSituation.resize(2 * height - 1, std::vector<Edge>(width));
    for (int x1 = 0; x1 < 2 * height - 1; x1++) // �߳�ʼ��
    {
        if (x1 % 2 == 0) // ����
        {
            for (int y1 = 0; y1 < width - 1; y1++)
            {
                edgeSituation[x1][y1].x = x1;
                edgeSituation[x1][y1].y = y1;
            }
        }
        if (x1 % 2 == 1) // ����
        {
            for (int y1 = 0; y1 < width; y1++)
            {
                edgeSituation[x1][y1].x = x1;
                edgeSituation[x1][y1].y = y1;
            }
        }
    }
    for (int x1 = 0; x1 < height - 1; x1++) // ���ʼ��
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
