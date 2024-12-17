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

struct Coordinates
{
    double X;
    double Y;
};

#endif // BASICCLASSES_H
