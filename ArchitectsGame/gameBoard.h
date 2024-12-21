#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include <QWidget>
#include "game.h"
#include <QPixmap>
#include <QTimer>
#include <QMessageBox>
#include <QPainter>
#include <QFile>
#include <QMouseEvent>
#include <cmath>
#include <QDebug>
#include <QEventLoop>

#include "gameOverDialog.h"

const int aiThinkingTime = 500;

class gameBoard : public QWidget
{
    Q_OBJECT

public:
    explicit gameBoard(Game *gameInstance, QWidget *parent = nullptr);
    ~gameBoard();

    short getSituation; // 0表示正在进行游戏，1表示平局，2表示胜利，3表示失败，4表示双人对战模式结束。
    gameOverDialog *gameOverDialogWindow;

protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;

private:
    Game *game;
    void loadImages();

    int size; // 边的宽度/高度（px）。
    double updateSizes();

    // 图片
    QPixmap squareEmptyPixmap;
    QPixmap squareBluePixmap;
    QPixmap squareOrangePixmap;
    QPixmap squareBlackPixmap;
    QPixmap edgeWhitePixmap;
    QPixmap edgeBlackPixmap;
    QPixmap edgeBluePixmap;
    QPixmap edgeOrangePixmap;

    void drawGameBoard(QPainter &painter);
    void drawEdges(QPainter &painter);
    void drawSquares(QPainter &painter);
    Edge selectEdgeByClicking(int x, int y, QMouseEvent *event);
    void nextStepFuction();
    void aiStep(Color color);
    void endAndSettlement();
    void sleep(int time);
};

#endif // GAMEBOARD_H
