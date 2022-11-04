/**
 * @file Assignment1.cpp
 * @author Hammad Anwer (2021189) and Mian Akbar Jan (2021295)
 * @brief The driver code for the entire program
 * 
 * To compile the file run g++ Assignment1.cpp GridList.cpp -o assign1.exe
 * To run the file execute the assign1.exe file with the command ./assign1
 * 
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
    cout << "6. Search a phone number by number (faster search)" << endl;
    cout << "7. Display all numbers" << endl;
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
            //exception handling
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
        case 7:
        {
            list.displayNodes();
            break;
        }
        case 0:
            break;
        default:
        cout << "You entered an incorrect choice. Please enter again!" << endl;
        }
        
        

    } while (choice != 0);
}