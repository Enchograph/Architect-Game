#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include <QWidget>
#include "game.h"
#include <QPixmap> // 用于加载图片

class gameBoard : public QWidget
{
    Q_OBJECT

public:
    explicit gameBoard(Game *gameInstance, QWidget *parent = nullptr);
    ~gameBoard();

protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void resizeEvent(QResizeEvent *event) override; // 添加resizeEvent

private:
    Game *game;        // 游戏逻辑
    void loadImages(); // 加载图片

    int size;           // 尺寸
    void updateSizes(); // 更新方格和边的大小

    // 图片
    QPixmap squareEmptyPixmap;
    QPixmap squareBluePixmap;
    QPixmap squareOrangePixmap;
    QPixmap squareBlackPixmap;
    QPixmap edgeUnselectedPixmap;
    QPixmap edgeSelectedPixmap;

    void drawGameBoard(QPainter &painter); // 绘制整个游戏棋盘
    void drawEdges(QPainter &painter);     // 绘制边
    void drawSquares(QPainter &painter);   // 绘制方格
};

#endif // GAMEBOARD_H
