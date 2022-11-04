#pragma once
#include "stack.h"

class String
{
private:
    string equation; // input equation
    Stack temp;      // temporary stack to perform computation
    vector<string> Postfix;

public:
    String()
    {
        equation = "";
        temp.push("(");
        Postfix = {};
    }

    String(const string &s)
    {
        equation = s;
        equation.push_back(')');
        temp.changeLength(equation.length());
        temp.push("(");
        Postfix = {};
    }

    void PrintPostfix()
    {
        cout <<endl << "Postfix equation: ";
        for (int i = 0; i < Postfix.size(); i++)
        {
            cout << Postfix[i];
        }
        cout << endl << endl;
    }

    void PrintOriginal() { cout << equation << endl; }

    bool checkPostfix()
    {
        if (Postfix.size() == 0)
        {
            return false;
        }
        return true;
    }
    void enterAnotherString(const string &s)
    {
        equation = s;
        equation.push_back(')');
        Postfix = {};
        temp.makeEmpty();
        temp.changeLength(equation.length());
        temp.push("(");
    }
    int setPrecedence(const string &);                      // sets precedence of each operator
    bool comparePrecedence(const string &, const string &); // compares which operator has a higher precedence
    vector<string> convert();
    vector<string> convertToTokens(const string &str); // converts string to postfix
    string calculate();                                // calculates the answer of the input equation
    bool Operator(const char &c);
    string removeSpaces(string str);
    bool OperatorButString(const string &str);
    // checks if a character is an operator or not
    string add(const string &a, const string &b)
    {
        int num1 = stoi(a);
        int num2 = stoi(b);
        int ans = num1 + num2;
        string res = to_string(ans);
        return res;
    }
    string subtract(const string &a, const string &b)
    {
        int num1 = stoi(a);
        int num2 = stoi(b);
        int ans = num1 - num2;
        string res = to_string(ans);
        return res;
    }
    string multiply(const string &a, const string &b)
    {
        int num1 = stoi(a);
        int num2 = stoi(b);
        int ans = num1 * num2;
        string res = to_string(ans);
        return res;
    }
    string divide(const string &a, const string &b)
    {
        int num1 = stoi(a);
        int num2 = stoi(b);
        if (num2 == 0)
        {
            throw invalid_argument("Cannot divide by 0");
        }
        int ans = num1 / num2;
        string res = to_string(ans);
        return res;
    }
    string power(const string &a, const string &b)
    {
        int num1 = stoi(a);
        int num2 = stoi(b);
        int ans = pow(num1, num2);
        string res = to_string(ans);
        return res;
    }
};