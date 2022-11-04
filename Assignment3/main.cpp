#include "BST+.h"

#define read(type, var) \
    type var;           \
    std::cin >> var;

void menu()
{
    cout << "Choose one of the following options: \n\n";
    cout << "1)Insert Node\n";
    cout << "2)Delete Node\n";
    cout << "3)Search Node\n";
    cout << "4)Display Nodes InOrder\n";
    cout << "5)Display Nodes PostOrder\n";
    cout << "6)Display Nodes PreOrder\n";
    cout << "7)Make Tree Empty\n";
    cout << "8)Exit\n\n";
}

int main()
{
    menu();

    BST<int> tree;
    cout << "Your option is: ";
    read(int, option)

        while (option != 8)
    {
        switch (option)
        {
        case 1:
        {
            cout << "Enter the value you want to insert: ";
            read(int, value);
            tree.insertNode(value);
            break;
        }
        case 2:
        {
            cout << "Enter the value you want to delete: ";
            read(int, valToDelete)
                tree.remove(valToDelete);
            break;
        }
        case 3:
        {
            cout << "Enter the value you want to search: ";
            read(int, valToSearch)
                tree.searchNode(valToSearch);

            break;
        }
        case 4:
        {
            tree.showNodesInOrder();
            break;
        }
        case 5:
        {
            tree.showNodesPreOrder();

            break;
        }
        case 6:
        {
            tree.showNodesPostOrder();
            break;
        }
        case 7: 
        {
            tree.makeTreeEmpty();
            break;
        }
        default:
            break;
        };
        menu();
        cout << "Your option is: ";
        cin >> option;
    }

    return 0;
}