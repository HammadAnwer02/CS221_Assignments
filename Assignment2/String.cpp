/**
 * @file stack.cpp
 * @author Hammad Anwer (2021189) and Mian Akbar Jan (2021295)
 * @brief Implementation of String class
 *
 */

#include "String.h"


int String::setPrecedence(const string &c1)
{
    if (c1.compare("+") == 0 || c1.compare("-") == 0)
    { // add and minus has the lowest precedence
        return -1;
    }
    else if (c1.compare("*") == 0 || c1.compare("/") == 0)
    { // multiply and divide has the second highest precedence
        return 1;
    }
    else if (c1.compare("^") == 0)
    { // power has the highest precedence
        return 2;
    }
    return 99;
}

bool String::Operator(const char &c)
{
     if (c=='+'|| c=='-'|| c=='*'|| c=='/'|| c=='^'){
        return true;
    }
    return false;
}

bool String::comparePrecedence(const string &c1, const string &c2)
{
    int n1 = setPrecedence(c1);
    int n2 = setPrecedence(c2);
    if (n1 == n2)
    {
        return 1;
    }
    else if (n1 < n2)
    {
        return 1;
    }
    else if (n1 > n2)
    {
        return 0;
    }
    return 0;
}

string String::removeSpaces(string str)
{
    string withoutSpaces = "";
    for (int i = 0; i< str.length(); i++) {
        if (str.at(i) != ' ') {
            withoutSpaces.push_back(str.at(i));
        }
    }
    return withoutSpaces;
}



vector<string> String::convertToTokens(const string &str)
{   vector<string> wordVector;
    string toPush;
    int i =0;

    while (i < str.length())
    {   
        char c = str.at(i);
        if (!Operator(c) && str[i] != '(' && str[i] != ')') {
            toPush.push_back(str[i]);
            i++;
            continue;
        }
        else if (str[i] == '(' || str[i] == ')') {
            if (toPush.compare("") != 0){
                wordVector.push_back(toPush);
                toPush = "";
            }
            toPush = str.at(i);
            wordVector.push_back(toPush);
            toPush = "";
            i++;
        }

        else{ 
            if (toPush.compare("") != 0){
                wordVector.push_back(toPush);
                toPush = "";
            }
            toPush = str.at(i);
            wordVector.push_back(toPush);
            toPush = "";
            i++;
        }

    }
    return wordVector;

}

void printVectorString(const vector<string> str)
{
    for (int i = 0; i < str.size(); i++)
    {
        cout << str[i] << endl;
    }
}

bool String::OperatorButString(const string &str) {
    if (str.compare("+") == 0 || str.compare("-") == 0 || str.compare("*")  == 0|| str.compare("/") == 0 || str.compare("^") == 0){
        return true;
    }
    return false;
}

vector<string> String::convert()
{
    vector<string> tokens = convertToTokens(equation);
    for (int i = 0; i < tokens.size();i++)
    {

        string token = tokens[i];

       
        if (token.compare("(") == 0){
            temp.push(token); 
        }
        else if (OperatorButString(token)){
            // pop from stack only if precedence of whatever operator is lesser than the one already in the stack
            while(comparePrecedence(token, temp.Top()) && temp.Top().compare("(") != 0){
                Postfix.push_back(temp.Top());
                temp.pop();
            }
            temp.push(token);
        }
        else if (token.compare(")") == 0){
            while (!temp.isEmpty() && temp.Top().compare("(") != 0){
            Postfix.push_back(temp.Top());
            temp.pop();
            }
            temp.pop();
        }
        else{
          Postfix.push_back(token);
        }
    }
    return Postfix;
}

string String::calculate()
{
    Stack Calc(Postfix.size());
    vector<string> s = Postfix;
    for (int i = 0; i < Postfix.size(); i++)
    {
        string token = Postfix[i];
        if (!OperatorButString(token))
        {
            Calc.push(token);
        }
        else
        {
            string num1 = Calc.Top();
            Calc.pop();
            string num2 = Calc.Top();
            Calc.pop();
            char option = token.at(0);
            switch (option)
            {
            case '+':
            {
                string a = add(num2, num1);
                Calc.push(a);
                break;
            }
            case '-':
            {
                string a = subtract(num2, num1);
                Calc.push(a);
                break;
            }
            case '*':
            {
                string a = multiply(num2, num1);
                Calc.push(a);
                break;
            }
            case '/':
            {
                try
                {
                string a = divide(num2, num1);
                Calc.push(a);
                }
                catch(const std::exception& e)
                {
                    std::cerr << e.what() << '\n';
                }
                break;
            }
            case '^':
            {
                string a = power(num2, num1);
                Calc.push(a);
                break;
            }
            }
        }
    }
    return Calc.Top();
}