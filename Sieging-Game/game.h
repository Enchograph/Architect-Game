#ifndef GAME_H
#define GAME_H

#include "basicClasses.h"
#include <vector>
#include <cstdlib>
#include <ctime>
#include <QDebug>

class Game
{
private:
    int width;
    int height;

    std::vector<std::vector<Cell>> cellSituation;
    std::vector<std::vector<Edge>> edgeSituation;

    Color playerNow;
    Difficulty difficulty;
    InitialState initialState;

public:
    Game(int width1, int height1, InitialState initialState1, Difficulty difficulty1);

    bool playerExtraTurn;

    int getHeight() { return height; }
    int getWidth() { return width; }
    Cell &getCell(int x, int y) { return cellSituation[x][y]; }
    Edge &getEdge(int x, int y) { return edgeSituation[x][y]; }
    Color getPlayerNow() { return playerNow; }
    InitialState getInitialState() { return initialState; }
    void setPlayer(Color a) { playerNow = a; }
    Difficulty getDifficulty() { return difficulty; }

    void selectEdge(int x, int y, Color player);
    void checkCell(int x, int y, Color player);
    // void nextTurn();
    void checkAndChange(int x, int y, Color player);
    bool checkGameOver();
    int countPlayerCells(Color player) const;
    short gameOver();
    void reset();
    bool optionalGrid (int x,int y);


    Edge *simpleAiLogic();
    Edge *mediumAiLogic();
    Edge *hardAiLogic();
    Edge *aiLogic(Difficulty a);
};

#endif // GAME_H
