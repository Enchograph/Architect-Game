#include "gameBoard.h"
#include <QPainter>
#include <QPixmap>
#include <QFile>
#include <QMouseEvent> // 添加头文件
#include <cmath>
#include <iostream>

using std::cout, std::endl;

gameBoard::gameBoard(Game *gameInstance, QWidget *parent) : QWidget(parent), game(gameInstance)
{
    loadImages(); // 加载图片

    // 设置为自适应大小
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding); // 允许 gameBoard 在父窗口中扩展
}

gameBoard::~gameBoard() = default;

void gameBoard::loadImages()
{
    // 加载PNG图片（这些图片需要事先准备好并通过资源文件管理）
    squareEmptyPixmap = QPixmap(":/new/prefix1/resources/WhiteInside.png");
    squareBluePixmap = QPixmap(":/new/prefix1/resources/BlueInside.png");
    squareOrangePixmap = QPixmap(":/new/prefix1/resources/OrangeInside.png");
    edgeUnselectedPixmap = QPixmap(":/new/prefix1/resources/WhiteEdge.png");
    edgeSelectedPixmap = QPixmap(":/new/prefix1/resources/BlackEdge.png");
}

void gameBoard::resizeEvent(QResizeEvent *event)
{
    // 获取父窗口的较短边长度
    int newSize = qMin(width(), height());

    // 设置新的游戏板大小
    setFixedSize(newSize, newSize); // 使其保持正方形

    // 更新方格和边的大小
    updateSizes();

    // 调用父类的resizeEvent
    QWidget::resizeEvent(event);
}

void gameBoard::updateSizes()
{
    double w = width() / (5 * game->getWidth() + 1);
    double h = height() / (5 * game->getHeight() + 1);
    w > h ? size = h : size = w;
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

                // 根据边的选择状态绘制不同的边图片
                QPixmap edgePixmap = edge.isSelected ? edgeSelectedPixmap : edgeUnselectedPixmap;

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

                // 根据边的选择状态绘制不同的边图片
                QPixmap edgePixmap = edge.isSelected ? edgeSelectedPixmap : edgeUnselectedPixmap;

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

    // 根据鼠标点击的位置和方格大小来计算点击的行列
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
        cout << "1" << endl;
    }
    else if (manhattanDistance2 <= size)
    {
        resX = y * 2 + 1;
        resY = x;
        cout << "2" << endl;
    }
    else if (manhattanDistance3 <= size)
    {
        resX = y * 2 + 1;
        resY = x + 1;
        cout << "3" << endl;
    }
    else if (manhattanDistance4 <= size)
    {
        resX = y * 2 + 2;
        resY = x;
        cout << "4" << endl;
    }
    else
    {
        return;
    }
    cout << x << y << " " << event->x() << " " << event->y() << endl;
    if(game->getEdge(resX, resY).isSelected)return;
    game->selectEdge(resX, resY, game->getPlayer()); // 更新游戏状态

    update(); // 更新界面
    game->nextTurn();
}
