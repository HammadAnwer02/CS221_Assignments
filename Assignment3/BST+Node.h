#include <iostream>

using namespace std;


template<class T>
class BSTNode {
    public:
    T value;
    int count;
    BSTNode *left;
    BSTNode *right;

    BSTNode () {
        left = right = nullptr;
        count = 1;
    }
    BSTNode (const T& v = 0, BSTNode *l =  nullptr, BSTNode *r = nullptr) {
        value = v;
        left = nullptr;
        right = nullptr;
        count = 1;
    }
};