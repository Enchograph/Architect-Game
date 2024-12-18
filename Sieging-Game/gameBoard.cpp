#include "gameBoard.h"
#include <QPainter>
#include <QPixmap>
#include <QFile>
#include <QMouseEvent>
#include <cmath>
#include <iostream>
#include "sleepFuction.h"

using std::cout;
using std::endl;

const int aiThinkingTime = 500;

gameBoard::gameBoard(Game *gameInstance, QWidget *parent) : QWidget(parent), game(gameInstance)
{
    loadImages(); // 加载图片

    // 设置为自适应大小
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding); // 允许 gameBoard 在父窗口中扩展
}

gameBoard::~gameBoard() = default;

void gameBoard::loadImages()
{
    // 加载PNG图片
    squareEmptyPixmap = QPixmap(":/new/prefix1/resources/WhiteInside.png");
    squareBluePixmap = QPixmap(":/new/prefix1/resources/BlueInside.png");
    squareOrangePixmap = QPixmap(":/new/prefix1/resources/OrangeInside.png");
    edgeWhitePixmap = QPixmap(":/new/prefix1/resources/WhiteEdge.png");
    edgeBlackPixmap = QPixmap(":/new/prefix1/resources/BlackEdge.png");
    edgeBluePixmap = QPixmap(":/new/prefix1/resources/BlueEdge.png");
    edgeOrangePixmap = QPixmap(":/new/prefix1/resources/OrangeEdge.png");
}

void gameBoard::resizeEvent(QResizeEvent *event)
{
    setGeometry((parentWidget()->width() - updateSizes()*(5 * game->getWidth() + 1)) / 2, (parentWidget()->height() - updateSizes()*(5 * game->getHeight() + 1)) / 2, parentWidget()->width(),parentWidget()->height());
    //setGeometry(0,0, width(),height());



     // 更新棋盘内元素的大小
    update();      // 触发重新绘制
    QWidget::resizeEvent(event); // 调用父类处理
}

double gameBoard::updateSizes()
{
    double w = width() / (5 * game->getWidth() + 1);
    double h = height() / (5 * game->getHeight() + 1);
    w > h ? size = h : size = w;
    return size;
}

void gameBoard::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    drawGameBoard(painter); // 绘制整个游戏界面
}

void gameBoard::drawGameBoard(QPainter &painter)
{
    // 先绘制边
    drawEdges(painter);

    // 然后绘制方格
    drawSquares(painter);

    cout<<"paint once."<<endl;

}

void gameBoard::drawEdges(QPainter &painter)
{
    for (int x1 = 0; x1 < 2 * game->getHeight() - 1; x1++) // 遍历每一条边
    {
        if (x1 % 2 == 0) // 横线
        {
            for (int y1 = 0; y1 < game->getWidth() - 1; y1++)
            {
                Edge &edge = game->getEdge(x1, y1);

                QPixmap edgePixmap;  // = edge.isSelected ? edgeSelectedPixmap : edgeUnselectedPixmap;

                if(edge.color==white)
                {
                    edgePixmap = edgeWhitePixmap;
                }
                else if (edge.color==blue && edge.turnsAfterSelected==1)
                {
                    edgePixmap = edgeBluePixmap;
                }
                else if (edge.color==orange && edge.turnsAfterSelected==1)
                {
                    edgePixmap = edgeOrangePixmap;
                }
                else
                {
                    edgePixmap = edgeBlackPixmap;
                }

                QTransform transform;
                transform.rotate(90);                                      // 旋转图片 90 度
                QPixmap rotatedPixmap = edgePixmap.transformed(transform); // 获取旋转后的图片

                // 绘制横向边（旋转后的图片）
                painter.drawPixmap(y1 * 5 * size + size, x1 * 2.5 * size, 4 * size, size, rotatedPixmap);
            }
        }
        if (x1 % 2 == 1) // 竖线
        {
            for (int y1 = 0; y1 < game->getWidth(); y1++)
            {
                Edge &edge = game->getEdge(x1, y1);

                QPixmap edgePixmap;  // = edge.isSelected ? edgeSelectedPixmap : edgeUnselectedPixmap;

                if(edge.color==white)
                {
                    edgePixmap = edgeWhitePixmap;
                }
                else if (edge.color==blue && edge.turnsAfterSelected==1)
                {
                    edgePixmap = edgeBluePixmap;
                }
                else if (edge.color==orange && edge.turnsAfterSelected==1)
                {
                    edgePixmap = edgeOrangePixmap;
                }
                else
                {
                    edgePixmap = edgeBlackPixmap;
                }


                painter.drawPixmap(y1 * 5 * size, (x1 - 1) / 2 * 5 * size + size, size, 4 * size, edgePixmap);
            }
        }
    }
}

void gameBoard::drawSquares(QPainter &painter)
{
    for (int x1 = 0; x1 < game->getHeight() - 1; x1++) // 遍历每一个格
    {
        for (int y1 = 0; y1 < game->getWidth() - 1; y1++)
        {
            Cell &cell = game->getCell(x1, y1);

            // 根据方格的颜色选择相应的图片
            QPixmap squarePixmap;
            switch (cell.color)
            {
            case blue:
                squarePixmap = squareBluePixmap;
                break;
            case orange:
                squarePixmap = squareOrangePixmap;
                break;
            case black:
                squarePixmap = squareBlackPixmap;
                break;
            case white:
            default:
                squarePixmap = squareEmptyPixmap;
                break;
            }

            // 绘制方格
            painter.drawPixmap(y1 * 5 * size + size, x1 * 5 * size + size, 4 * size, 4 * size, squarePixmap);
        }
    }
}


void gameBoard::mousePressEvent(QMouseEvent *event)
{
    // updateSizes();

    int y = ceil(event->y() / (5 * size) - 0.1); // 根据点击的 Y 坐标确定行
    int x = ceil(event->x() / (5 * size) - 0.1); // 根据点击的 X 坐标确定列
    // 暂时还不清楚这里用向上取整反而能跑通的原因，稍后详加分析。

    if (x < 0 || y < 0 || x >= game->getWidth() || y >= game->getHeight())
    {
        return;
    }

    double manhattanDistance1 = abs(3 * size + 5 * x * size - event->x()) + abs(0.5 * size + 5 * y * size - event->y());
    double manhattanDistance4 = abs(3 * size + 5 * x * size - event->x()) + abs(0.5 * size + 5 * size + 5 * y * size - event->y());
    double manhattanDistance2 = abs(3 * size + 5 * y * size - event->y()) + abs(0.5 * size + 5 * x * size - event->x());
    double manhattanDistance3 = abs(3 * size + 5 * y * size - event->y()) + abs(0.5 * size + 5 * x * size + 5 * x - event->x());

    int resX, resY;
    if (manhattanDistance1 <= size)
    {
        resX = 2 * y;
        resY = x;
        cout << "上边";
    }
    else if (manhattanDistance2 <= size)
    {
        resX = y * 2 + 1;
        resY = x;
        cout << "左边";
    }
    else if (manhattanDistance3 <= size)
    {
        resX = y * 2 + 1;
        resY = x + 1;
        cout << "右边";
    }
    else if (manhattanDistance4 <= size)
    {
        resX = y * 2 + 2;
        resY = x;
        cout << "下边";
    }
    else
    {
        return;
    }
    cout <<" 鼠标："<< event->x() << " " << event->y()<<" "<<"格子("<< x <<","<< y << ")"  << endl;
    if(game->getEdge(resX, resY).color!=white)return;

    switch(game->getInitialState())
    {
    case comptr :
        game->selectEdge(resX, resY, orange);
        break;
    case human :
        game->selectEdge(resX, resY, blue);
        break;
    case player1 :
        game->selectEdge(resX, resY, game->getPlayerNow());
        break;

    }

    update(); // 更新界面



    if(!game->checkGameOver())
    {

        if(game->playerExtraTurn)
        {
            if(game->getInitialState()==comptr)
            {
                // none
            }
            if(game->getInitialState()==human)
            {
                // none
            }
            if(game->getInitialState()==player1)
            {
                // none
            }
        }
        else
        {
            if(game->getInitialState()==comptr)
            {
                sleep(aiThinkingTime);

                Edge * nextStep = game->aiLogic(game->getDifficulty());
                int x = nextStep->x;
                int y = nextStep->y;
                game->selectEdge(x,y,blue);

                update(); // 更新界面


                while(game->playerExtraTurn&&(!game->checkGameOver()))
                {
                    sleep(aiThinkingTime);

                    Edge * nextStep = game->aiLogic(game->getDifficulty());
                    int x = nextStep->x;
                    int y = nextStep->y;
                    game->selectEdge(x,y,blue);

                    update(); // 更新界面

                }
            }
            if(game->getInitialState()==human)
            {
                sleep(aiThinkingTime);

                Edge * nextStep = game->aiLogic(game->getDifficulty());
                int x = nextStep->x;
                int y = nextStep->y;
                game->selectEdge(x,y,orange);

                update(); // 更新界面


                while(game->playerExtraTurn&&(!game->checkGameOver()))
                {
                    sleep(aiThinkingTime);

                    Edge * nextStep = game->aiLogic(game->getDifficulty());
                    int x = nextStep->x;
                    int y = nextStep->y;
                    game->selectEdge(x,y,orange);

                    update(); // 更新界面

                }
            }
            if(game->getInitialState()==player1)
            {
                if(game->getPlayerNow()==blue)
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
    update();
}
