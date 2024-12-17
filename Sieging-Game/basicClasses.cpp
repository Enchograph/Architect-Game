#include "basicClasses.h"

#include <iostream>

using std::cout;
using std::endl;

Cell::Cell(Edge *topE, Edge *leftE, Edge *rightE, Edge *bottomE, int x1, int y1)
{
    topEdge = topE;
    leftEdge = leftE;
    rightEdge = rightE;
    bottomEdge = bottomE;
    x = x1;
    y = y1;
}

Cell::Cell() { color = white; }

bool Cell::check(Color player)
{
    if (topEdge->isSelected && leftEdge->isSelected && rightEdge->isSelected && bottomEdge->isSelected)
    {
        color = player;
        // 再加一个给方格组件染色/改背景图片的步骤。
        return true;
    }
    return false;
}

Edge *Cell::unselectedEdgesLeft()
{
    int count = 0;
    if (topEdge->isSelected)
        count++;
    if (leftEdge->isSelected)
        count++;
    if (rightEdge->isSelected)
        count++;
    if (bottomEdge->isSelected)
        count++;
    if (count != 3)
    {
        return NULL;
    }
    else
    {
        if (!(topEdge->isSelected))
            return topEdge;
        if (!(leftEdge->isSelected))
            return leftEdge;
        if (!(rightEdge->isSelected))
            return rightEdge;
        if (!(bottomEdge->isSelected))
            return bottomEdge;
    }
    cout << "unselectedEdgesLeft Error!" << endl;
    return NULL;
}
