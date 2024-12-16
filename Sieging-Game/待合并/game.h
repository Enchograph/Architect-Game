#ifndef GAME_H
#define GAME_H

#include <vector>
#include <cstdlib> // 用于 rand 和 srand
#include <ctime>   // 用于 time

enum Color
{
    white,
    blue,
    orange,
    black
};

enum Mode
{
    vsComptr,
    vsHuman
};

enum Difficulty
{
  simple,
    medium,
    hard
};

struct Edge
{
    bool isSelected = false;
    int x;
    int y;
};

class Cell
{
public:
    Edge *topEdge;
    Edge *leftEdge;
    Edge *rightEdge;
    Edge *bottomEdge;

    Color color = white;

    int x;
    int y;

    Cell(Edge *topE, Edge *leftE, Edge *rightE, Edge *bottomE, int x1, int y1);
    Cell();
    bool check(Color player);
    Edge *unselectedEdgesLeft();
};

class Game
{
private:
    int width;
    int height;
    std::vector<std::vector<Cell>> cellSituation;
    std::vector<std::vector<Edge>> edgeSituation;
    Mode playMode;
    Color playerNow;
    Difficulty difficulty;

public:
    Game(int width1, int height1, Mode playerMode1,Difficulty difficulty1);

    int getHeight(){return height;}
    int getWidth(){return width;}
    Cell &getCell(int x, int y) { return cellSituation[x][y]; }
    Edge &getEdge(int x, int y) { return edgeSituation[x][y]; }
    Mode getMode(){return playMode;}
    Color getPlayer(){return playerNow;}
    void setPlayer(Color a){playerNow=a;}
    Difficulty getDifficulty(){return difficulty;}

    void selectEdge(int x, int y, Color player);
    void checkCell(int x, int y, Color player);
    void nextTurn();
    bool checkGameOver();
    int countPlayerCells(Color player) const;
    void gameOver();
    void reset();

    Edge * simpleAiLogic();
    Edge * mediumAiLogic();
    Edge * hardAiLogic();
    Edge * aiLogic(Difficulty a);
};

#endif // GAME_H
