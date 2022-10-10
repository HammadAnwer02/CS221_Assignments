

#include "GridList.h"

GridList::GridList(int r, int c)
{
    rows = r;
    cols = c;
    numElements = 0;
    maxSize = r * c;
}

void GridList::displayNodes() const
{
    if (isEmpty()) 
    {
        cout << "\n\nThere are no nodes to display\n\n";
        return;
    }
    GridListNode *temp;
    temp = head;

    GridListNode *curr = temp;
    while (curr != tail)
    {
        cout << curr->peopleInfo;
        cout << "Position: (" << curr->row << ", " << curr->col << ")" << endl;
        if (curr->next != nullptr)
        {
            curr = curr->next;
        }
        else
        {
            if (temp->bottom != nullptr)
            {
                curr = temp->bottom;
                temp = temp->bottom;
            }
        }
    }
    cout << tail->peopleInfo;
    cout << "Position: (" << tail->row << ", " << tail->col << ")" << endl;
}

void GridList::insertNode()
{

    if (isFull())
    {
        throw invalid_argument("\n\nMax size reached\n\n");
    }
    else
    {
        People p;
        cin >> p;
        if (searchNode(p.info[phoneNumber], phoneNumber) != nullptr)
        {
            throw invalid_argument("\n\n***********\nPhone number already exists\n***********\n\n");
        }

        if (numElements == 0)
        {
            head = tail = new GridListNode(p);
        }
        else
        {
            GridListNode *temp = head;
            int currTailRow = tail->row;
            int currTailCol = tail->col;
            // if not at the end of the coloumn
            if (currTailCol != cols - 1)
            {

                // if at the first row
                if (currTailRow == 0)
                {
                    // a simple doubly linked list
                    GridListNode *newNode = new GridListNode(p, currTailRow, currTailCol + 1, nullptr, nullptr, nullptr, tail);
                    tail->next = newNode;
                    tail = newNode;
                }
                else
                {
                    GridListNode *newNode = new GridListNode(p, currTailRow, currTailCol + 1, tail->top->next, nullptr, nullptr, tail);
                    tail->top->next->bottom = newNode;
                    tail->next = newNode;
                    tail = newNode;
                }
            }
            else
            {
                if (currTailRow != rows - 1)
                {
                    while (temp->row != currTailRow)
                    {
                        temp = temp->bottom;
                    }
                    // are temp is at the start of thw row are tail pointer currently is in
                    temp->bottom = new GridListNode(p, currTailRow + 1, 0, temp, nullptr, nullptr, nullptr);
                    tail = temp->bottom;
                }
                else
                {
                    throw invalid_argument("\n\nSomething went terribaly wrong\n\n");
                }
            }
        }
        numElements++;
    }

    this->sortList();
}

void GridList::sortList()
{

    bool isSorted = false;

    GridListNode *lastNode = tail;

    while (!isSorted)
    {
        GridListNode *temp = head;
        GridListNode *curr = temp;
        isSorted = true;
        while (curr != lastNode)
        {
            GridListNode *nextNode;
            if (curr->next != nullptr)
            {
                nextNode = curr->next;
            }
            else
            {
                if (temp->bottom != nullptr)
                {
                    nextNode = temp->bottom;
                    temp = temp->bottom;
                }
                else
                {
                    break;
                }
            }

            int isCompare = curr->peopleInfo.info[phoneNumber].compare(nextNode->peopleInfo.info[phoneNumber]);
            if (isCompare > 0)
            {
                isSorted = false;
                swap(curr->peopleInfo, nextNode->peopleInfo);
            }

            if (nextNode != lastNode)
            {
                curr = nextNode;
            }
            else
            {
                lastNode = lastNode->back;
            }
        }
    }
}

void GridList::deleteNode()
{
    if (isEmpty())
    {
        throw invalid_argument("\n\nNo elements exist in the list to delete\n\n");
    }
    else
    {
        cout << "Enter phone number to delete: ";
        string pNum;
        cin >> pNum;
        GridListNode *pToDelete = searchNode(pNum, PeopleInfo::phoneNumber);
        if (pToDelete)
        {
            if (numElements == 1)
            {
                delete tail;
                head = tail = nullptr;
                return;
            }
            // get to the highest possible value for a string
            pToDelete->peopleInfo.info[phoneNumber] = "~";
            this->sortList();
            int currTailRow = tail->row;
            int currTailCol = tail->col;

            if (currTailRow == 0)
            {
                tail = tail->back;
                delete tail->next;
                tail->next = nullptr;
            }
            else if (currTailCol == 0)
            {
                GridListNode *temp = head;
                while (temp->row != currTailRow - 1)
                {
                    temp = temp->bottom;
                }
                temp->bottom = nullptr;
                while (temp->col != cols - 1)
                {
                    temp = temp->next;
                }
                delete tail;
                tail = temp;
            }
            else
            {
                tail->top->bottom = nullptr;
                tail = tail->back;
                delete tail->next;
                tail->next = nullptr;
            }
        }
        else
        {
            throw invalid_argument("Value does not exist");
        }
    }
}

GridListNode *GridList::fastSearch(string searchElem) const {
    GridListNode *temp = head;
    if (isEmpty())
    {
        return nullptr;
    }

    if (numElements == 1)
    {
        if (temp->peopleInfo.info[phoneNumber].compare(searchElem) == 0)
        {
            return temp;
        }
        else
        {
            return nullptr;
        }
    }
    // int currNodeRow = temp->row;

    // if element at head is greater than the element being searched the value does not exist
    while (temp->bottom != nullptr && temp->peopleInfo.info[phoneNumber].compare(searchElem) <= 0)
    {
        temp = temp->bottom;
    }

    if (temp->bottom == nullptr)
    {
        if (temp->top != nullptr && temp->peopleInfo.info[phoneNumber].compare(searchElem) > 0)
        {
            temp = temp->top;
        }
        GridListNode *curr = temp;
        while (curr != nullptr && curr->peopleInfo.info[phoneNumber].compare(searchElem) != 0)
        {
            curr = curr->next;
        }
        return curr;
    }
    else
    {
        temp = temp->top;
        GridListNode *curr = temp;
        while (curr != nullptr && curr->peopleInfo.info[phoneNumber].compare(searchElem) != 0)
        {
            curr = curr->next;
        }
        return curr;
    }
    return nullptr;
}

GridListNode *GridList::normalSearch(string searchElem, const PeopleInfo &pInfo) const  {
    GridListNode *temp = head;
    if (isEmpty())
    {
        return nullptr;
    }

    if (numElements == 1)
    {
        if (temp->peopleInfo.info[pInfo].compare(searchElem) == 0)
        {
            return temp;
        }
        else
        {
            return nullptr;
        }
    }

    while (temp != nullptr) {
        GridListNode *curr = temp;
        while (curr != nullptr && curr->peopleInfo.info[pInfo].compare(searchElem) != 0) {
            curr = curr->next;
        }
        if (curr != nullptr) {
            return curr;
        }
        temp = temp->bottom;
    }
    // if element does not exist this will return a null pointer
    return temp;
}

GridListNode *GridList::searchNode(string searchElem, const PeopleInfo &pInfo) const
{
    if (pInfo == phoneNumber) {
        return fastSearch(searchElem);
    } else {
        return normalSearch(searchElem, pInfo);
    }
}
