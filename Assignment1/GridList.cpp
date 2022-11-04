/**
 * @file GridList.cpp
 * @author Hammad Anwer (2021189) and Mian Akbar Jan (2021295)
 * @brief The implementation of GridList class
 */

#include "GridList.h"

GridList::GridList(int r, int c) //function that initializes the max rows, columns, maxSize(max no. of elements) & initial elements to 0
{
    rows = r;
    cols = c;
    numElements = 0;
    maxSize = r * c;
}

void GridList::displayNodes() const //function that displays all nodes by traversing the linked list from head to tail
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
        // if not end of coloumn traverse to next node in the same row
        if (curr->next != nullptr)
        {
            curr = curr->next;
        }
        else
        {
            // if now already in the last row go to the row one below current one
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

void GridList::insertNode() //function that inserts node at tail, then sorts the linked list to place the Node in ordered position
{

    if (isFull()) //checks if list is full
    {
        throw invalid_argument("\n\nMax size reached\n\n");
    }
    else
    {
        People p;
        cin >> p;
        
        if (searchNode(p.info[phoneNumber], phoneNumber) != nullptr) //if phone no. already exists, it won't be added again
        {
            throw invalid_argument("\n\n***********\nPhone number already exists\n***********\n\n");
        }

        if (numElements == 0) //if no elements in linked list, then first node will be head and tail
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
                //second row onwards, new node created and links with top and back made
                else
                {
                    GridListNode *newNode = new GridListNode(p, currTailRow, currTailCol + 1, tail->top->next, nullptr, nullptr, tail);
                    tail->top->next->bottom = newNode;
                    tail->next = newNode;
                    tail = newNode;
                }
            }
             //if at the end of column
            else
            {
                 //until last row reached
                if (currTailRow != rows - 1)
                {
                    //move temp down
                    while (temp->row != currTailRow)
                    {
                        temp = temp->bottom;
                    }
                    // our temp is at the start of the row our tail pointer currently is in
                    temp->bottom = new GridListNode(p, currTailRow + 1, 0, temp, nullptr, nullptr, nullptr);
                    tail = temp->bottom;
                }
                else
                {
                    throw invalid_argument("\n\nSomething went terribaly wrong\n\n");
                }
            }
        }
        numElements++; //increases number of elements with each node addition
    }

    this->sortList();
}

void GridList::sortList() //sorts list in ascending order based on phone number
{


    // this function runs like bubble sort does in arrays
    bool isSorted = false;

    // the last pointer will be moved to the prev node with each sorting iteration
    GridListNode *lastNode = tail;

    while (!isSorted)
    {
        GridListNode *temp = head;
        GridListNode *curr = temp;
        isSorted = true;
        while (curr != lastNode)
        {
            GridListNode *nextNode;
            if (curr->next != nullptr) //until last node in a row reached
            {
                nextNode = curr->next;
            }
            else
            {
                if (temp->bottom != nullptr) //until last row reached
                {
                    nextNode = temp->bottom;
                    temp = temp->bottom;
                }
                else
                {
                    break;
                }
            }
            //swaps nodes
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
    //checks if list is empty
    if (isEmpty())
    {
        throw invalid_argument("\n\nNo elements exist in the list to delete\n\n");
    }
    else
    {
        cout << "Enter phone number to delete: ";
        string pNum;
        cin >> pNum;
        //finds node in list
        GridListNode *pToDelete = searchNode(pNum, PeopleInfo::phoneNumber);
        if (pToDelete)
        {
            // if the only element in the list
            if (numElements == 1)
            {
                delete tail;
                head = tail = nullptr;
                return;
            }
            // get to the highest possible value for a string
            pToDelete->peopleInfo.info[phoneNumber] = "~";
            this->sortList(); //sends node to delete to the tail
            int currTailRow = tail->row;
            int currTailCol = tail->col;

            if (currTailRow == 0) //if only one row in the list
            {
                tail = tail->back;
                delete tail->next;
                tail->next = nullptr;
            }
            else if (currTailCol == 0) //if node is in the first column of the list
            {
                GridListNode *temp = head;
                while (temp->row != currTailRow - 1)
                {
                    temp = temp->bottom;
                }
                temp->bottom = nullptr; //makes the bottom of the second last row null
                while (temp->col != cols - 1)
                {
                    temp = temp->next; //traverses to the end of the second last row
                }
                delete tail; //deletes original tail
                tail = temp; //makes last node in second last row the tail
            }
            else //any node apart from those present in the first row or first column
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

    if (numElements == 1) //if only one number in the list
    {
        if (temp->peopleInfo.info[phoneNumber].compare(searchElem) == 0)
        {
            return temp; //if that number is equal to the number to be searched
        }
        else
        {
            return nullptr;
        }
    }


    // if element at head is greater than the element being searched the value does not exist
    while (temp->bottom != nullptr && temp->peopleInfo.info[phoneNumber].compare(searchElem) <= 0)  //moves temp downwards until a value that is greater than or equal to the element to search is found
    {
        temp = temp->bottom;
    }

    if (temp->bottom == nullptr)
    {
        if (temp->top != nullptr && temp->peopleInfo.info[phoneNumber].compare(searchElem) > 0) //if phone number is smaller than first element in a row, temp moves one up
        {
            temp = temp->top;
        }
        GridListNode *curr = temp;
        while (curr != nullptr && curr->peopleInfo.info[phoneNumber].compare(searchElem) != 0)
        {
            curr = curr->next; //moves in the specified row until number to be searched is found
        }
        return curr;
    }
    else // if element to be searched was found in the row before the last one (loop exited early)
    {
        //moves temp one up and searches in that row
        temp = temp->top;
        GridListNode *curr = temp;
        while (curr != nullptr && curr->peopleInfo.info[phoneNumber].compare(searchElem) != 0)
        {
            curr = curr->next;
        }
        return curr;
    }
    // if element does not exist this will return a null pointer
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
        return fastSearch(searchElem); //faster search for phone number
    } else {
        return normalSearch(searchElem, pInfo); //normal search for name, address and email
    }
}
