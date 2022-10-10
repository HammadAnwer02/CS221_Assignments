#pragma once
#include "GridListNode.h"

/**
 * @brief The definition of the class
 *
 */

class GridList
{
private:
    int rows, cols;
    // keeps track of the number of elements in the list
    int numElements;
    int maxSize;
    GridListNode *head, *tail;

    bool isFull() const { return numElements == maxSize; }
    bool isEmpty() const { return numElements == 0; }
    GridListNode *normalSearch(string searchElem, const PeopleInfo &pInfo) const;
    GridListNode *fastSearch(string searchElem) const;
    
public:
    GridList(int r = 0, int c = 0);
    void insertNode();
    void deleteNode();
    void displayNodes() const;
    GridListNode *searchNode(string searchElem, const PeopleInfo &pInfo) const;
    void sortList();
};

