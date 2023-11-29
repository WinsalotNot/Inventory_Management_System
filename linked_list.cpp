#include "WindowsAPI.h"
using namespace std;

int Val2;
void linkedList::insertValue(string d, string n, int q, float p){
    Node* tmpNode = new Node;
    tmpNode->date = d;
    tmpNode->name = n;
    tmpNode->quantity = q;
    tmpNode->price = p;
    tmpNode->next = nullptr;
    tmpNode->previous = nullptr;

    if(head == nullptr){
        head = tmpNode;
    } else{
        Node* temp = head;
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        temp->next = tmpNode;
        tmpNode->previous = temp;
    }
}
void linkedList::deleteNode(int val, HWND hWnd) {
    Node* currentNode = head;
    int currentPosition = 1;

    while (currentNode != nullptr && currentPosition < val) {
        currentNode = currentNode->next;
        currentPosition++;
    }

    if (currentNode == nullptr) {
        Val2 = MessageBox(hWnd, "Empty Record", "Please Fill in Records!", MB_OK | MB_ICONERROR);
        if(Val2 == IDOK)
        {return;}
        return;
    }

    if (currentNode->previous != nullptr) {
        currentNode->previous->next = currentNode->next;
    }

    if (currentNode->next != nullptr) {
        currentNode->next->previous = currentNode->previous;
    }

    if (currentNode == head) {
        head = currentNode->next;
    }

    delete currentNode;
    Val2 = MessageBox(hWnd, "Records Deleted\nDon't forget to re-display to see the edited records :>", "NICE!", MB_OK);
    if(Val2 == IDOK)
    {return;}
}
void linkedList::replaceValue(int position, string n, int what, HWND hWnd) {
    Node* currentNode = head;
    for (int currentPosition = 1; currentNode != nullptr && currentPosition != position; currentPosition++)
    {
        currentNode = currentNode->next;
    }
    
    if (currentNode == nullptr) {
        Val2 = MessageBox(hWnd, "NOTHING TO REPLACE", "Please Retry!", MB_OK);
        if(Val2 == IDOK)
        {return;}
    }

    if (what == 1) {
        currentNode->date = n;
    } else if (what == 2) {
        currentNode->name = n;
    } else if (what == 3) {
        char tempArr[5000];
        strcpy(tempArr, n.c_str());
        if (isdigit(tempArr[0]))
        {
            currentNode->quantity = stoi(n);
        } else {
            Val2 = MessageBox(hWnd, "Make sure the input new data is an integer!", "INVALID TYPE", MB_OK | MB_ICONWARNING);
                if (Val2 == IDOK)
                {return;}
        }
    } else if (what == 4) {
        char tempArr2[5000];
        strcpy(tempArr2, n.c_str());
        if (isdigit(tempArr2[0]))
        {
            currentNode->price = stof(n);
        } else {
            Val2 = MessageBox(hWnd, "Make sure the input new data is an int or float!", "INVALID TYPE", MB_OK | MB_ICONWARNING);
            if (Val2 == IDOK)
            {return;}
        }
    } else {
        Val2 = MessageBox(hWnd, "Data Field Does Not Exist!", "Please Retry!", MB_OK);
        if(Val2 == IDOK)
        {return;}
    }

    Val2 = MessageBox(hWnd, "Data Replaced!\nMake sure to re-display the screen by pressing the button again :>", "NICE!", MB_OK | MB_ICONEXCLAMATION);
    if (Val2 == IDOK)
    {return;}
}

bool linkedList::DecreaseQuantity(int where, int howmuch, HWND hWnd)
{
    Node* currentNodeDec = head;
    int currentPosition = 1;
    int placeholder = 0;

    while (currentNodeDec != nullptr && currentPosition < where) {
        currentNodeDec = currentNodeDec->next;
        currentPosition++;
    }
    if (currentNodeDec == nullptr) {
        cout << "no stock to decrease" << endl;
        return false;
    }
    if (currentNodeDec->quantity < howmuch) {
    Val2 = MessageBox(hWnd, "Someone's Eager to Make Money ;>\nUnfortunately, Not Enough Stock :<", "Hint: Maybe Try Selling A Sufficient Amount :>", MB_OK | MB_ICONWARNING);
    if (Val2 == IDOK)
    {return false;}
    }
    currentNodeDec->quantity = currentNodeDec->quantity - howmuch;
    return true;
}

void linkedList::addQuantity(int position, int add, HWND hWnd) {
    Node* currentNode = head;
    int currentPosition = 1;

    while (currentNode != nullptr && currentPosition < position) {
        currentNode = currentNode->next;
        currentPosition++;
    }
    if (currentNode == nullptr) {
        Val2 = MessageBox(hWnd, "INVALID POSITION!", "Please Retry!", MB_OK | MB_ICONERROR);
        if(Val2 == IDOK)
        {return;}
        return;
    }
    currentNode->quantity += add;
    Val2 = MessageBox(hWnd, "Stock Added!\nDon't forget to re-display to see the edited records :>", "NICE!", MB_OK | MB_ICONEXCLAMATION);
    if(Val2 == IDOK)
    {return;}
}

void linkedList::print(float val) {
    Node* go = head;
    for (float i = 0; i < val; i++){go = go->next;}
    cout << "Name: " << go->name << " Quantity: " << go->quantity << " Price: Rp. " << go->price <<endl;
    }

void linkedList::printAllName() {
    Node* go = head;
    cout << "No\tName" << endl;
    while (go != nullptr) {
        int i = 1;
        cout << i <<".\t" << go->name <<endl;
        go = go->next;
        i++;
    }
    cout << endl;
} 

void linkedList::printAllNameQuantity() {
    Node* go = head;
    cout << "No \t Name \t Quantity" << endl;
    while (go != nullptr) {
        int i = 1;
        cout << i <<".\t" << go->name << "\t" << go->quantity << endl;
        go = go->next;
        i++;
    }
    cout << endl;
} 


char* linkedList::printAll() {
    Node* go = head;
    char Out[10000];
    Out[0] = '\0';
    int i = 1;

    while (go != nullptr) {
        int IndLen = 0;
        int QtyLen = 0;
        char anotherI[5000];
        sprintf(anotherI, "%1d", i);
        while (anotherI[IndLen] != '\0')
        {
            IndLen++;
        }
        
        char anotherQty[5000];
        sprintf(anotherQty, "%1d", go->quantity);
        while (anotherQty[QtyLen] != '\0')
        {
            QtyLen++;
        }

        char anotherPrice[5000];
        sprintf(anotherPrice, "%.2f", go->price);

        string name = go->name;
        int length = name.length();
        char* anotherName = new char[length + 1];
        strcpy(anotherName, name.c_str());

        string Date = go->date;
        int lengthTwo = Date.length();
        char* anotherDate = new char[lengthTwo + 1];
        strcpy(anotherDate, Date.c_str());

        char No[] = {"No"};
        char DateArr[] = {"Date"};
        char Name[] = {"Name"};
        char Quantity[] = {"Quantity"};
        char Price[] = {"Price"};
        strcat(Out, PrintCategoryHeader(No, DateArr, Name, Quantity, Price, 
        IndLen, lengthTwo, length, QtyLen));

        strcat(Out, anotherI);
        strcat(Out, ".\t");
        strcat(Out, anotherDate);
        strcat(Out, "\t");
        strcat(Out, anotherName);
        strcat(Out, "\t");
        strcat(Out, anotherQty);
        strcat(Out, "\t");
        strcat(Out, anotherPrice);
        strcat(Out, "\r\n");

        go = go->next;
        delete[] anotherName;
        delete[] anotherDate;
        i++;
        strcat(Out, "\r\n");
    }

    return strdup(Out);
}

char* linkedList::PrintCategoryHeader(char* head1, char* head2, char* head3, char* head4, char* head5, 
int LIndex, int LDate, int LName, int LQty)
{
    int i = 1;
    const int charLim = 7;
    char Out2[5000];
    Out2[0] = '\0';

    strcpy(Out2, head1);
    strcat(Out2, "\t");
    if (LIndex > charLim)
    {
        strcat(Out2, "\t");
        if (LIndex % 8 == 0 && LIndex - 8 != 0)
        {
            int times = LIndex / 8;
            times--;
            while (times)
            {
                strcat(Out2, "\t");
            }
        }
    }
    
    strcat(Out2, head2);
    strcat(Out2, "\t");
    if (LDate > charLim)
    {
        strcat(Out2, "\t");
        if (LDate % 8 == 0 && LDate - 8 != 0)
        {
            int times = LDate / 8;
            times--;
            while (times)
            {
                strcat(Out2, "\t");
            }
        }
    }

    strcat(Out2, head3);
    strcat(Out2, "\t");
    if (LName > charLim)
    {
        strcat(Out2, "\t");
        if (LName % 8 == 0 && LName - 8 != 0)
        {
            int times = LName / 8;
            times--;
            while (times)
            {
                strcat(Out2, "\t");
            }
        }
    }

    strcat(Out2, head4);
    strcat(Out2, "\t");
    if (LQty > charLim)
    {
        strcat(Out2, "\t");
        if (LQty % 8 == 0 && LQty- 8 != 0)
        {
            int times = LQty / 8;
            times--;
            while (times)
            {
                strcat(Out2, "\t");
            }
        }
    }

    strcat(Out2, head5);
    strcat(Out2, "\r\n");

    return strdup(Out2);
}

int linkedList::checkSize() {
    Node* go = head;
    int i = 0;
    while (go != nullptr) {
        i++;
        go = go->next;
    }
    return i;
}

int linkedList::getQuantity(int input) {
    Node* go = head;
    int i=1;
    while (i !=input) {
        go = go->next;
        i++;
    }
    return go->quantity;
}

float linkedList::getPrice(int input) {
    Node* go = head;
    int i=1;
    while (i !=input) {
        go = go->next;
        i++;
    }
    return go->price;
}

string linkedList::getName(int input) {
    Node* go = head;
    int i=1;
    while (i !=input) {
        go = go->next;
        i++;
    }
    return go->name;
}

string linkedList::getDate(int input) {
    Node* go = head;
    int i=1;
    while (i !=input) {
        go = go->next;
        i++;
    }
    return go->date;
}

void linkedList::sortData(HWND hWnd){
    if (!head || !head->next) {
        Val2 = MessageBox(hWnd, "No Fields To Sort, Sowwy... :<", "I'm Useless :'<", MB_OK | MB_ICONWARNING);
        if (Val2 == IDOK)
        {return;}
    }

    Node* end;
    Node* temp;
    Node* prev;
    Node* r;
    Node* curr;
        
    for (end = nullptr; end!= head->next; end = prev){
        for(r = prev = head; prev->next != end; r = prev, prev = prev->next){
            curr = prev->next;
            for(int n = 0; curr->name[n-1] == prev->name[n-1]; n++){

                if(curr->name[n] < prev->name[n]){
                    prev->next = curr->next;
                    curr->next = prev;

                    if(prev != head){
                        r->next = curr;
                    }else{
                        head = curr;
                    }
                    temp = prev;
                    prev = curr;
                    curr = temp;
                    
                }

            }   
        }   
            
    }  
    Val2 = MessageBox(hWnd, "Yay Record Sorted!", "Very Sorted OMG! :>", MB_OK | MB_ICONWARNING);
    if (Val2 == IDOK)
    {return;}
}

Node* linkedList::getHead(){
    return head;
}
int functions::checkEmpty() {
    linkedList catalog;
    if (catalog.getHead() == nullptr) {
        cout << "Linked list is empty." << endl;
        return 0; // List is empty
    } else {
        int size = catalog.checkSize();
        cout << "Linked list size: " << size << endl;
        return size;
    }
}
