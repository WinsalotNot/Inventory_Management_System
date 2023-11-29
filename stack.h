#ifndef stack
#include <stack>
#include <iostream>
using namespace std;
#include "link_list.h"

class StackNode {
public:
    float revenue;
    string name;
    int quantity;
    float price;
    StackNode* next;
    StackNode(float revenue, string name, int quantity, float price);
};

class Stack {
    StackNode* top;
public:
    Stack() { top = nullptr; }
    void push(float revenue, string name, int quantity, float price);
    void pop();
    char* PrintTotal();
    char* printStack();
    void clearStack();
};



#endif