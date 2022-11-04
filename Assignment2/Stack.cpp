/**
 * @file stack.cpp
 * @author Hammad Anwer (2021189) and Mian Akbar Jan (2021295)
 * @brief Implementation of stack class
 * 
 * 
 */

#include "Stack.h"
void Stack::changeLength(const int size){
    this->size = size;
    array = new string[size];
}
void Stack:: push (const string &value){
    if (isFull()){
        throw invalid_argument("\n\nStack is full\n\n");
    }
    else {
        top++;
        array[top] = value;
    }
}
string Stack:: pop (){
    if (isEmpty()){
        cout << "Stack is empty" << endl;
    }
    else {
        string num = array[top];
        top--;
        return num;
    }
    return "";
}
string Stack:: Top(){
     if (isEmpty()){
        throw invalid_argument("\n\nStack is empty\n\n");
    }
    else {
        string num = array[top];
        return num;
    }
    return "";
}

