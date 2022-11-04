/**
 * @file stack.cpp
 * @author Hammad Anwer (2021189) and Mian Akbar Jan (2021295)
 * @brief Main file
 *
 */

#include <cctype>
#include <iostream>

#include "String.h"

void menu()
{
    cout << "1. Convert to Postfix" << endl;
    cout << "2. Calculate" << endl;
    cout << "3. Print original equation" << endl;
    cout << "4. Print Postfix equation" << endl;
    cout << "5. Enter another String" << endl;
    cout << "6. Exit" << endl << endl;
    cout << "Enter an option: ";
}
int main()
{
    cout << "Enter string: ";
    string s;
    cin >> s;
    cout << endl;
    String S(s);
    // checks if string contains any letters
    bool check = false;
    for (int i = 0; i < s.length(); i++)
    {
        if (isalpha(s.at(i)))
        {
            check = true;
            break;
        }
    }
    int option;
    do
    {

        menu();
        cin >> option;

        switch (option)
        {
        case 1:
        {
            vector<string> r = S.convert();
            break;
        }
        case 2:
        {
            if (check == true)
            {
                cout << "Cannot calculate" << endl;
                break;
            }
            else if (S.checkPostfix() == false)
            {
                cout << "Cannot calculate, convert to Postfix first!" << endl;
                break;
            }
            else
            {
                string r = S.calculate();
                cout << endl
                     << "Answer: " << r << endl
                     << endl;
                break;
            }
        }
        case 3:
        {
            cout << endl
                 << "Original Equation: " << s << endl
                 << endl;
            break;
        }
        case 4:
        {
            S.PrintPostfix();
            break;
        }
        case 5:
        {
            cout << "Enter another string: ";
            cin >> s;
            S.enterAnotherString(s);
            // checks if string contains any letters
            bool check = false;
            for (int i = 0; i < s.length(); i++)
            {
                if (isalpha(s.at(i)))
                {
                    check = true;
                    break;
                }
            }
        }
        case 6:
        {
            break;
        }
        default:
        {
            cout << "Enter valid option: ";
            break;
        }
        }
    } while (option != 6);
    return 0;
}