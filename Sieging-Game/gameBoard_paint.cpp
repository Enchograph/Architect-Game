#include "gameBoard.h"

void gameBoard::loadImages()
{
    // 加载PNG图片
    squareEmptyPixmap = QPixmap(":/resources/WhiteInside.png");
    squareBluePixmap = QPixmap(":/resources/BlueInside.png");
    squareOrangePixmap = QPixmap(":/resources/OrangeInside.png");
    edgeWhitePixmap = QPixmap(":/resources/WhiteEdge.png");
    edgeBlackPixmap = QPixmap(":/resources/BlackEdge.png");
    edgeBluePixmap = QPixmap(":/resources/BlueEdge.png");
    edgeOrangePixmap = QPixmap(":/resources/OrangeEdge.png");
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

    qDebug()<<"paint once.";

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

