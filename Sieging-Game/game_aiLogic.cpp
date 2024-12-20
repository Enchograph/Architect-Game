#include "game.h"


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
            if (edgeSituation[randomX][randomY].color==white)
            {
                qDebug()<<"ai "<<"random: "<<randomX<<randomY;
                return &edgeSituation[randomX][randomY];
            }
        }
        else
        {
            randomX = rand() % (height - 1);
            randomX = randomX * 2 + 1;
            randomY = rand() % width;
            if (edgeSituation[randomX][randomY].color==white)
            {
                qDebug()<<"ai "<<"random: "<<randomX<<randomY;
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
                    if (edgeSituation[x1][y1].color==white)
                    {
                        qDebug()<<"ai "<<"traverse: "<<x1<<y1;
                        return &edgeSituation[x1][y1];
                    }
                }
            }
            if (x1 % 2 == 1) // 竖线
            {
                for (int y1 = 0; y1 < width; y1++)
                {
                    if (edgeSituation[x1][y1].color==white)
                    {
                        qDebug()<<"ai "<<"traverse: "<<x1<<y1;
                        return &edgeSituation[x1][y1];
                    }
                }
            }
        }
    qDebug() << "aiLogic Error!";
    return NULL;
}

Edge *Game::mediumAiLogic()
{
    for (int x1 = 0; x1 < height - 1; x1++) // 先遍历每一格找局部最优解
    {
        for (int y1 = 0; y1 < width - 1; y1++)
        {
            if (cellSituation[x1][y1].unselectedEdge().theEdgeLefted != NULL)
            {
                qDebug()<<"ai "<<"strategy: "<<x1<<y1;
                return cellSituation[x1][y1].unselectedEdge().theEdgeLefted;
            }
        }
    }

    return simpleAiLogic();
}

Edge *Game::hardAiLogic()
{
    for (int x1 = 0; x1 < height - 1; x1++) // 先遍历每一格找局部最优解
    {
        for (int y1 = 0; y1 < width - 1; y1++)
        {
            if (cellSituation[x1][y1].unselectedEdge().theEdgeLefted != NULL)
            {
                qDebug()<<"ai "<<"strategy: "<<x1<<y1;
                return cellSituation[x1][y1].unselectedEdge().theEdgeLefted;
            }
        }
    }

    srand(static_cast<unsigned int>(time(0))); // 设置随机数种子
       int x, y;
       for (int z = 0; z < 10; z++)
       {
           if (rand() % 2 == 0)
           {
               x = rand() % height;
               x *= 2;
               y = rand() % (width - 1);
               if (x == 0) // 最上方的一行，检查下面的方块
               {
                   if(optionalGrid(x / 2, y)&& edgeSituation[x][y].color==white)
                       return &edgeSituation[x][y];
               }
               else if (x / 2 - 1 == height - 2) // 最下方的一行，检查上面的方块
               {
                   if(optionalGrid(x / 2 - 1, y)&& edgeSituation[x][y].color==white)
                           return &edgeSituation[x][y];
               }
               else // 中间的行，两边都检查
               {
                   if(optionalGrid(x / 2, y)&&
                   optionalGrid(x / 2 - 1, y)&& edgeSituation[x][y].color==white)return &edgeSituation[x][y];
               }
           }
           else
           {
               x = rand() % (height - 1);
               x = x * 2 + 1;
               y = rand() % width;
               if (y == 0) // 最左端的一行，检查右边的方块
               {
                   if(optionalGrid((x - 1) / 2, y)&& edgeSituation[x][y].color==white)
                           return &edgeSituation[x][y];
               }
               else if (y == width - 1) // 最右端的一行，检查左边的方块
               {
                   if(optionalGrid((x - 1) / 2, y - 1)&& edgeSituation[x][y].color==white)
                           return &edgeSituation[x][y];
               }
               else
               {
                   if(optionalGrid((x - 1) / 2, y)&&
                   optionalGrid((x - 1) / 2, y - 1)&& edgeSituation[x][y].color==white)                            return &edgeSituation[x][y];

               }
           }
       }
    for (int x = 0; x < 2 * height - 1; x++) // 遍历每一条边
    {
        if (x % 2 == 0) // 横线
        {
            for (int y = 0; y < width - 1; y++){
                if (x == 0) // 最上方的一行，检查下面的方块
                {
                    if(optionalGrid(x / 2, y)&& edgeSituation[x][y].color==white)
                        return &edgeSituation[x][y];
                }
                else if (x / 2 - 1 == height - 2) // 最下方的一行，检查上面的方块
                {
                    if(optionalGrid(x / 2 - 1, y)&& edgeSituation[x][y].color==white)
                            return &edgeSituation[x][y];
                }
                else // 中间的行，两边都检查
                {
                    if(optionalGrid(x / 2, y)&&
                    optionalGrid(x / 2 - 1, y)&& edgeSituation[x][y].color==white)return &edgeSituation[x][y];
                }
            }
        }
        if (x % 2 == 1) // 竖线
        {
            for (int y = 0; y < width; y++)
            {
                if (y == 0) // 最左端的一行，检查右边的方块
                {
                    if(optionalGrid((x - 1) / 2, y)&& edgeSituation[x][y].color==white)
                            return &edgeSituation[x][y];
                }
                else if (y == width - 1) // 最右端的一行，检查左边的方块
                {
                    if(optionalGrid((x - 1) / 2, y - 1)&& edgeSituation[x][y].color==white)
                            return &edgeSituation[x][y];
                }
                else
                {
                    if(optionalGrid((x - 1) / 2, y)&&
                    optionalGrid((x - 1) / 2, y - 1)&& edgeSituation[x][y].color==white)                            return &edgeSituation[x][y];

                }
            }
        }
    }


    return mediumAiLogic();
}

bool Game::optionalGrid (int x,int y)
{
    if(cellSituation[x][y].unselectedEdge().num!=2)return true;
    else return false;
}
