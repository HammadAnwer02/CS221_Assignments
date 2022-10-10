/**
 * @file Assignment1.cpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-10-07
 * 
 * @copyright Copyright (c) 2022
 * 
 */



#include "GridList.h"


void menu()
{
    cout << "----MENU----" << endl;
    cout << "1. Insert a phone Number" << endl;
    cout << "2. Delete a phone Number" << endl;
    cout << "3. Search a phone number by name" << endl;
    cout << "4. Search a phone number by address" << endl;
    cout << "5. Search a phone number by email" << endl;
    cout << "6. Display all numbers" << endl;
    cout << "7. Search a phone number by number" << endl;
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
            try
            {
                list.insertNode();
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
            
            try
            {
                list.deleteNode();
            }
            catch (const std::exception &e)
            {
                std::cerr << e.what() << '\n';
                break;
            }
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
            break;
        }
        case 7:
        {
            cout << "Enter phone number to search: ";
            string phoneAdd;
            cin.ignore();
            getline(cin, phoneAdd);
            GridListNode *searched = list.searchNode(phoneAdd, phoneNumber);
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
        case 0:
            break;
        default:
        cout << "You entered an incorrect choice. Please enter again!" << endl;
        }
        
        

    } while (choice != 0);
}