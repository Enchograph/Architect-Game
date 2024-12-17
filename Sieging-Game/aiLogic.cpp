#include "game.h"

#include <iostream>

using std::cout;
using std::endl;

Edge *Game::aiLogic(Difficulty a)
{



    switch (a)
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

Edge *Game::simpleAiLogic()
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
                cout<<"ai "<<"random: "<<randomX<<randomY<<endl;
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
                cout<<"ai "<<"random: "<<randomX<<randomY<<endl;
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
                    if (edgeSituation[x1][y1].isSelected == false)
                    {
                        cout<<"ai "<<"traverse: "<<x1<<y1<<endl;
                        return &edgeSituation[x1][y1];
                    }
                }
            }
            if (x1 % 2 == 1) // 竖线
            {
                for (int y1 = 0; y1 < width; y1++)
                {
                    if (edgeSituation[x1][y1].isSelected == false)
                    {
                        cout<<"ai "<<"traverse: "<<x1<<y1<<endl;
                        return &edgeSituation[x1][y1];
                    }
                }
            }
        }
    cout << "simpleAiLogic Error!" << endl;
    return NULL;
}

Edge *Game::mediumAiLogic()
{
    for (int x1 = 0; x1 < height - 1; x1++) // 先遍历每一格找局部最优解
    {
        for (int y1 = 0; y1 < width - 1; y1++)
        {
            if (cellSituation[x1][y1].unselectedEdgesLeft() != NULL)
            {
                cout<<"ai "<<"strategy: "<<x1<<y1<<endl;
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
                cout<<"ai "<<"random: "<<randomX<<randomY<<endl;
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
                cout<<"ai "<<"random: "<<randomX<<randomY<<endl;
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
                    if (edgeSituation[x1][y1].isSelected == false)
                    {
                        cout<<"ai "<<"traverse: "<<x1<<y1<<endl;
                        return &edgeSituation[x1][y1];
                    }
                }
            }
            if (x1 % 2 == 1) // 竖线
            {
                for (int y1 = 0; y1 < width; y1++)
                {
                    if (edgeSituation[x1][y1].isSelected == false)
                    {
                        cout<<"ai "<<"traverse: "<<x1<<y1<<endl;
                        return &edgeSituation[x1][y1];
                    }
                }
            }
        }
    cout << "mediumAiLogic Error!" << endl;
    return NULL;
}

Edge *Game::hardAiLogic()
{
    cout << "hardAiLogic Error!" << endl;
    return NULL;
}

// 行棋逻辑
