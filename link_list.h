#ifndef linkedlist
#define linkedlist
#include <iostream>
#include "WindowsAPI.h"

using namespace std;
class Node {
public:
    string date;
    string name;
    int quantity;
    float price;
    Node* next;
    Node* previous;
};

class linkedList{
private:
    Node* head;
public:
    linkedList() : head(nullptr) {}
    Node* getHead();
    void insertValue(string, string, int, float);
    void deleteNode(int, HWND);
    void replaceValue(int, string, int, HWND);
    bool DecreaseQuantity(int where, int howmuch, HWND hWnd);
    void addQuantity(int, int, HWND);
    void print(float);
    void printAllName();
    void printAllNameQuantity();
    char* PrintCategoryHeader(char* head1, char* head2, char* head3, char* head4, char* head5, 
    int LIndex, int LDate, int LName, int LQty);
    char* printAll();
    int checkSize();
    int getQuantity(int);
    float getPrice(int);
    string getName(int);
    string getDate(int);
    void sortData(HWND);
};

class functions {
public:
    int checkEmpty();
    void insertItem();
    void deleteItem();
    void printCatalog();
    void addStock(HWND);
    void replaceData();
};
#endif