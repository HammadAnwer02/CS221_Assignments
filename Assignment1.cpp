#include <iostream>
#include <string>
#include <exception>

using namespace std;

enum PeopleInfo
{
    phoneNumber,
    name,
    address,
    email
};

struct People
{
    string info[4];

    People(string p = "", string n = "", string a = "", string e = "")
    {
        info[phoneNumber] = p;
        info[name] = n;
        info[address] = a;
        info[email] = e;
    }
    People(const People &p)
    {
        info[phoneNumber] = p.info[phoneNumber];
        info[name] = p.info[name];
        info[address] = p.info[address];
        info[email] = p.info[email];
    }

    friend ostream &operator<<(ostream &output, const People &p)
    {
        output << "-------------------------------------" << endl;
        output << "Phone Number: " << p.info[phoneNumber] << endl;
        output << "Name: " << p.info[name] << endl;
        output << "Address: " << p.info[address] << endl;
        output << "Email: " << p.info[email] << endl << endl;
        return output;
    }
    friend istream &operator>>(istream &input, People &p)
    {
        cout << "Enter phone number: ";
        input >> p.info[phoneNumber];
        cout << "Enter name: ";
        input.ignore();
        getline(input, p.info[name]);
        cout << "Enter address: ";
        input.ignore();
        getline(input, p.info[address]);
        cout << "Enter email address (if any): ";
        input.ignore();
        getline(input, p.info[email]);
        return input;
    }
};

class GridListNode
{
    friend class GridList;

public:
    // stores the
    People peopleInfo;

    // stores the 4 pointers for each node
    GridListNode *top, *bottom, *back, *next;

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

class GridList
{
private:
    int rows, cols;
    // keeps track of the number of elements in the list
    int numElements;
    int maxSize;
    GridListNode *head, *tail;

public:
    GridList(int r = 0, int c = 0);
    void insertNode(const People &);
    void deleteNode(const string &pNumber);
    void displayNodes() const;
    GridListNode *searchNode(string searchElem, const PeopleInfo &pInfo) const;
    void sortList();
};

// set the matrix for the number of rows and cols consisted of the nodes
GridList::GridList(int r, int c)
{
    rows = r;
    cols = c;
    numElements = 0;
    maxSize = r * c;
}

void GridList::displayNodes() const
{
    GridListNode *temp;
    temp = head;

    GridListNode *curr = temp;
    while (curr != tail)
    {
        cout << curr->peopleInfo << endl;
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
    cout << tail->peopleInfo << endl;
}

void GridList::insertNode(const People &p)
{
    if (searchNode(p.info[phoneNumber], phoneNumber) != nullptr) {
        throw invalid_argument("***********Phone number already exists***********");
    }

    if (numElements < maxSize)
    {

        if (numElements == 0)
        {
            head = tail = new GridListNode(p);
        }
        else
        {
            GridListNode *temp = head;
            int currTailRow = tail->row;
            int currTailCol = tail->col;
            if (currTailCol != cols - 1)
            {

                if (currTailRow == 0)
                {
                    GridListNode *newNode = new GridListNode(p, currTailRow, currTailCol + 1, nullptr, nullptr, nullptr, tail);
                    tail->next = newNode;
                    tail = newNode;
                }
                else
                {
                    GridListNode *curr = temp;
                    while (temp->row != currTailRow - 1)
                    {
                        temp = temp->bottom;
                    }

                    while (curr->col != currTailCol + 1)
                    {
                        curr = curr->next;
                    }
                    GridListNode *newNode = new GridListNode(p, currTailRow, currTailCol + 1, curr, nullptr, nullptr, tail);
                    curr->bottom = newNode;
                    tail->next = newNode;
                    tail = newNode;
                }
            }
            else if (currTailRow != rows - 1)
            {

                // Our temp node is currently pointing towards the first row of the coloumn our tail node is in;
                while (temp->row != currTailRow)
                {
                    temp = temp->bottom;
                }
                GridListNode *newNode = new GridListNode(p, currTailRow + 1, 0, temp, nullptr);
                temp->bottom = newNode;
                tail = newNode;
            }
            // for last row
            else if (currTailRow == rows - 1)
            {
                if (currTailCol != cols - 1)
                {

                    GridListNode *curr = temp;
                    while (temp->row != currTailRow - 1)
                    {
                        temp = temp->bottom;
                    }

                    while (curr->col != currTailCol + 1)
                    {
                        curr = curr->next;
                    }
                    GridListNode *newNode = new GridListNode(p, currTailRow, currTailCol + 1, curr, nullptr, nullptr, tail);
                    curr->bottom = newNode;
                    tail->next = newNode;
                    tail = newNode;
                }
                else
                {
                    throw invalid_argument("********************\nSomething went terribly wrong\n***************************");
                }
            }
            else
            {
                throw invalid_argument("********************\nSomething went terribly wrong\n***************************");
            }
        }

        numElements++;
    }
    else
    {
        throw invalid_argument("Max size reached");
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

void GridList::deleteNode(const string &pNumber)
{
    if (numElements == 0) {
        throw invalid_argument("No elements exist in the list");
    }

    GridListNode *pToDelete = searchNode(pNumber, PeopleInfo::phoneNumber);
    if (pToDelete)
    {
        if (numElements == 1) {
            delete tail;
            head = tail = nullptr;
            return;
        }
        pToDelete->peopleInfo.info[phoneNumber]  = "9999999999999999";
        this->sortList();
        int currTailRow = tail->row;
        int currTailCol = tail->col;

        if (currTailRow == 0) {
            tail = tail->back;
            delete tail->next;
            tail->next = nullptr;
        } else if (currTailCol== 0){
            GridListNode *temp = head;
            while (temp->row != currTailRow - 1) {
                temp = temp->bottom;
            }
            temp->bottom = nullptr;
            while (temp->col != cols - 1) {
                temp = temp->next;
            }
            delete tail;
            tail = temp;

        } else  {
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
    this->displayNodes();
}

GridListNode *GridList::searchNode(string searchElem, const PeopleInfo &pInfo) const
{
    GridListNode *temp = head;
    GridListNode *curr = temp;
    /*
    if(curr->peopleInfo.info[phoneNumber]<temp->peopleInfo)
    
    */
    if (numElements == 0)
    {
        return nullptr;
    }

    if (numElements == 1)
    {
        if (curr->peopleInfo.info[pInfo].compare(searchElem) == 0)
        {
            return curr;
        }
        else
        {
            return nullptr;
        }
    }

    while (curr != tail)
    {
        
        if (curr->peopleInfo.info[pInfo].compare(searchElem) == 0)
        {
            return curr;
        }

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
            else
            {
                break;
            }
        }
    }

    if (curr->peopleInfo.info[pInfo].compare(searchElem) == 0) {
        return curr;
    } else {
        return nullptr;

    }
}

void menu()
{
    cout << "----MENU----" << endl;
    cout << "1. Insert a phone Number" << endl;
    cout << "2. Delete a phone Number" << endl;
    cout << "3. Search a phone number by name" << endl;
    cout << "4. Search a phone number by address" << endl;
    cout << "5. Search a phone number by email" << endl;
    cout << "6. Display all numbers" << endl;
    cout << "0. Exit!" << endl;
}

int main()
{
    int rows;
    int cols;
    cout << "Enter rows: ";
    cin >> rows;
    cout << "Enter columns: ";
    cin >> cols;
    GridList list(rows, cols);
    int choice;
    do
    {
        menu();
        cin >> choice;
        switch (choice)
        {
        case 1:
        {
            People p;
            cin >> p;
            try
            {
                list.insertNode(p);
            }
            catch (const std::exception &e)
            {
                std::cerr << e.what() << '\n';
                break;
            }
            break;
        }

        case 2:
        {
            cout << "Enter phone number to delete: ";
            string pNum;
            cin >> pNum;
            list.deleteNode(pNum);
            break;
        }
        case 3:
        {
            cout << "Enter name to search: ";
            string userName;
            cin.ignore();
            getline(cin, userName);
            GridListNode *searched = list.searchNode(userName, name);
            if (searched != nullptr)
            {
                cout << searched->peopleInfo;
            }
            else
            {
                cout << "Not found" << endl;
            }
            break;
        }
        case 4:
        {
            cout << "Enter address to search: ";
            string add;
            cin.ignore();
            getline(cin, add);
            GridListNode *searched = list.searchNode(add, address);
            if (searched != nullptr)
            {
                cout << searched->peopleInfo;
            }
            else
            {
                cout << "Not found" << endl;
            }
            break;
        }
        case 5:
        {
            cout << "Enter email to search: ";
            string emailAdd;
            cin.ignore();
            getline(cin, emailAdd);
            GridListNode *searched = list.searchNode(emailAdd, email);
            if (searched != nullptr)
            {
                cout << searched->peopleInfo;
            }
            else
            {
                cout << "Not found" << endl;
            }
            break;
        }
        case 6:
        {
            list.displayNodes();
        }
        case 0:
            break;
        }

    } while (choice != 0);
}