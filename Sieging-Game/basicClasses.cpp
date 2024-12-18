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
    if (topEdge->color!=white && leftEdge->color!=white && rightEdge->color!=white && bottomEdge->color!=white)
    {
        color = player;
        // 再加一个给方格组件染色/改背景图片的步骤。
        return true;
    }
    return false;
}

//Edge *Cell::unselectedEdgesLeft()
//{
//    int count = 0;
//    if (topEdge->color!=white)
//        count++;
//    if (leftEdge->color!=white)
//        count++;
//    if (rightEdge->color!=white)
//        count++;
//    if (bottomEdge->color!=white)
//        count++;
//    if (count != 3)
//    {
//        return NULL;
//    }
//    else
//    {
//        if (!(topEdge->color!=white))
//            return topEdge;
//        if (!(leftEdge->color!=white))
//            return leftEdge;
//        if (!(rightEdge->color!=white))
//            return rightEdge;
//        if (!(bottomEdge->color!=white))
//            return bottomEdge;
//    }
//    cout << "unselectedEdgesLeft Error!" << endl;
//    return NULL;
//}

UnselectedEdge Cell:: unselectedEdge()
{
    UnselectedEdge result;
    result.theEdgeLefted=NULL;

    int count = 0;
    if (topEdge->color!=white)
        count++;
    if (leftEdge->color!=white)
        count++;
    if (rightEdge->color!=white)
        count++;
    if (bottomEdge->color!=white)
        count++;

    switch(count)
    {
    case 0:
        result.num=4;
        break;
    case 1:
        result.num=3;
        break;
    case 2:
        result.num=2;
        break;
    case 3:
        result.num=1;
        if (!(topEdge->color!=white))
            result.theEdgeLefted=topEdge;
        if (!(leftEdge->color!=white))
            result.theEdgeLefted=leftEdge;
        if (!(rightEdge->color!=white))
            result.theEdgeLefted=rightEdge;
        if (!(bottomEdge->color!=white))
            result.theEdgeLefted=bottomEdge;
        break;
    case 4:
        result.num=0;
        break;

    }

    return result;
}
