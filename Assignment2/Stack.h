#pragma once
#include <iostream>
#include <string>
#include <exception>
#include <math.h>
#include <vector>

using namespace std;

class Stack
{
public:
    string *array;
    int size;
    int top;

public:
    Stack(int s)
    {
        size = s;
        array = new string[size];
        top = -1;
    }
    Stack()
    {
        size = 0;
        array = new string[size];
        top = -1;
    }
    void changeLength(const int);                   // changes length of temp stack based on the size of the equation
    void push(const string &value);                 // pushes element to the stack
    string pop();                                   // pops and returns the element from the stack
    string Top();                                   // returns the top of the stack without popping from the stack
    bool isFull() const { return top == size - 1; } // checks if the stack is full
    bool isEmpty() const { return top == -1; }      // checks if the stack is empty
    void makeEmpty() {
       while (!isEmpty()){
            pop();
        }
    }
};