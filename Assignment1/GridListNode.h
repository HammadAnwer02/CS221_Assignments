#include "People.h"


class GridListNode
{
    friend class GridList;

public:
    // stores the info for every person
    People peopleInfo;

    // stores the 4 pointers for each node
    GridListNode *top, *bottom, *back, *next;

    // stores the position of the node in the grid
    int row, col;

    GridListNode(GridListNode *topNode = nullptr, GridListNode *bottomNode = nullptr, GridListNode *nextNode = nullptr, GridListNode *previousNode = nullptr)
    {
        top = topNode;
        bottom = bottomNode;
        next = nextNode;
        back = previousNode;
    }

    GridListNode(const People &pInfo, int r = 0, int c = 0, GridListNode *t = nullptr, GridListNode *b = nullptr, GridListNode *n = nullptr, GridListNode *prev = nullptr)
    {
        peopleInfo = pInfo;
        row = r;
        col = c;
        top = t;
        bottom = b;
        next = n;
        back = prev;
    }
};
