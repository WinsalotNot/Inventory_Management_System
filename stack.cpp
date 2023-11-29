#include "WindowsAPI.h"
#include <stack>
#include <iostream>

using namespace std;

linkedList catalog;

StackNode::StackNode(float revenue, string name, int quantity, float price)
{
    this->revenue = revenue;
    this->name = name;
    this->quantity = quantity;
    this->price = price;
    this->next = nullptr;
}

void Stack::push(float revenue, string name, int quantity, float price){
    StackNode* temp = new StackNode(revenue, name, quantity, price);

    if (!temp) {
        cout << "\nStack Overflow";
        exit(1);
    }

    temp->next = top;
    top = temp;
}

void Stack::pop() {
    if (top == nullptr) {
        cout << "\nStack Underflow" << endl;
        return;
    }

    StackNode* temp = top;
    top = top->next;
    delete temp;
}

char* Stack::printStack() {
    StackNode* current = top;
    char stackOut[10000];
    stackOut[0] = '\0';
    int i = 1;
    strcpy(stackOut, "Sale History: \r\n");
    while (current != nullptr) {
        int S_IndLen = 0;
        int S_QtyLen = 0;
        int S_PriceLen = 0;
        char S_anotherI[5000];
        sprintf(S_anotherI, "%1d", i);
        while (S_anotherI[S_IndLen] != '\0')
        {
            S_IndLen++;
        }
        
        char S_anotherQty[5000];
        sprintf(S_anotherQty, "%1d", current->quantity);
        while (S_anotherQty[S_QtyLen] != '\0')
        {
            S_QtyLen++;
        }

        char S_anotherPrice[5000];
        sprintf(S_anotherPrice, "%.2f", current->price);
        while (S_anotherPrice[S_PriceLen] != '\0')
        {
            S_PriceLen++;
        }

        char S_anotherTotalPrice[5000];
        sprintf(S_anotherTotalPrice, "%.2f", current->revenue);

        string S_name = current->name;
        int S_length = S_name.length();
        char* S_anotherName = new char[S_length + 1];
        strcpy(S_anotherName, S_name.c_str());

        char No[] = {"No"};
        char Revenue[] = {"Revenue"};
        char Name[] = {"Name"};
        char Quantity[] = {"Quantity"};
        char Price[] = {"Price"};
        strcat(stackOut, catalog.PrintCategoryHeader(No, Name, Quantity, Price, Revenue, 
        S_IndLen, S_length, S_QtyLen, S_PriceLen));

        strcat(stackOut, S_anotherI);
        strcat(stackOut, ".\t");
        strcat(stackOut, S_anotherName);
        strcat(stackOut, "\t");
        strcat(stackOut, S_anotherQty);
        strcat(stackOut, "\t");
        strcat(stackOut, S_anotherPrice);
        strcat(stackOut, "\t");
        strcat(stackOut, S_anotherTotalPrice);
        strcat(stackOut, "\r\n");

        current = current->next;
        delete[] S_anotherName;
        i++;
        strcat(stackOut, "\r\n");
    }
    strcat(stackOut, PrintTotal());
    strcat(stackOut, "\r\n");
    return strdup(stackOut);
}

char* Stack::PrintTotal()
{
    float totalrev = 0;
    StackNode* current = top;
    while (current != nullptr)
    {
        totalrev = totalrev + current->revenue;
        current = current->next;
    }
    char TotalRev[1000], TotalRevOut[1001];
    sprintf(TotalRev, "%.2f", totalrev);
    strcpy(TotalRevOut, "Current Total = ");
    strcat(TotalRevOut, TotalRev);
    
    return strdup(TotalRevOut);
}
void Stack::clearStack() {
    while (top != nullptr) {
        StackNode* temp = top;
        top = top->next;
        delete temp;
    }
}
