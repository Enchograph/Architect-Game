#ifndef BASICCLASSES_H
#define BASICCLASSES_H

enum Color
{
    white,
    blue,
    orange,
    black
};

enum InitialState
{
    comptr,
    human,
    player1
};

enum Difficulty
{
  simple,
    medium,
    hard
};

struct Edge
{
    int x;
    int y;
    Color color=white;
    int turnsAfterSelected=0;
};

struct UnselectedEdge
{
    Edge * theEdgeLefted;
    int num;
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
    UnselectedEdge unselectedEdge();
};

struct Coordinates
{
    double X;
    double Y;
};

#endif // BASICCLASSES_H
