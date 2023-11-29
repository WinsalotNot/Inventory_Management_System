#include "WindowsAPI.h"
#include <tchar.h>
#include <string.h>
#include <iostream>
#include <stack>

#define CONFIRM_STOCKADD 1
#define CONFIRM_DELETION 2
#define DELETE_RECORD 3
#define GENERATE_BUTTON 4
#define DISPLAY_RECORD 6
#define CONFIRM_EDIT 7
#define EDIT_RECORD 9
#define STOCK_ADD 10
#define SELL_INV 11
#define CONFIRM_SELL 12
#define DISPLAY_SELL 13
#define SORT_RECORDS 14
#define REFRESH_BUTTON 15


//---global scope definition[START]---//

Window var;
functions func;
linkedList LL;
Stack stackfunc;
int Val, OutLength;
const int width = 600;
const int height = 500;
HWND hName, hDate, hPrice, hQty, hOutput, hLogo, hButton, hButton2,
hDispButton, hDispButton2, hDisplayInv, hDisplayInv2, hEditInv, hIndex, hEditWhich, hEditedData, DlgButton, hDlg, 
hDlg2, hDlg3, hDlg4, hDelete, hStockWhich, hStockMuch, hSellWhich, hSellMuch;
HMENU hMenu, hFileMenu, hSubFileMenu;
HBITMAP hButtonImage;
bool isDialogOpen = false;
bool isMenuItemAdded = false;
HWND hAge;
HBITMAP hLogoImage, hGenerateImage;
RECT rect;
stack<float> RevStack;
int diff = 0;

//---global scope definition[END]---//


LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
    case WM_COMMAND:
        switch (wParam)
        {
            case GENERATE_BUTTON:
                char Date[5000], Name[5000], Qty[5000], Price[5000], Output[180000];
                GetWindowText(hDate, Date, 5000);
                GetWindowText(hName, Name, 5000);
                GetWindowText(hQty, Qty, 5000);
                GetWindowText(hPrice, Price, 5000);

                if (strcmp(Date, "") == 0 || strcmp(Name, "") == 0 || strcmp(Qty, "") == 0 || strcmp(Price, "") == 0)
                {
                    Val = MessageBox(hWnd, "All Fields are Not Complete!", "ERROR!",
                    MB_OK | MB_ICONWARNING);
                    if (Val == IDOK)
                    {return 0;}
                    
                } else if (isdigit(Qty[0]) && isdigit(Price[0]))
                {
                    int TrueQty = atoi(Qty);
                    float TruePrice = atof(Price);
                    if (TrueQty > 2147483646)
                    {
                        Val = MessageBox(hWnd, "Value of Qty is more than Max Integer of 2147483647!", "EXCEEDING LIMIT", MB_OK | MB_ICONWARNING);
                        if (Val == IDOK)
                        {break;}
                    } else if (TruePrice > 9999999)
                    {
                        Val = MessageBox(hWnd, "Value of Price is More than Max float of 1000000.50!", "EXCEEDING LIMIT", MB_OK | MB_ICONWARNING);
                        if (Val == IDOK)
                        {break;}
                    } else {
                        LL.insertValue(Date, Name, TrueQty, TruePrice);
                    }
                } else
                {
                    Val = MessageBox(hWnd, "Please Enter in Digits in Quantity and Price Fields!", "INVALID TYPE", MB_OK | MB_ICONWARNING);
                    if (Val == IDOK)
                    {break;}
                }
                
                strcpy(Output, ""); //Clears texts from previous iterations
                strcat(Output, LL.printAll());
                SetWindowText(hOutput, Output);

                SendMessage(hOutput, EM_LINESCROLL, 0, 
                    SendMessage(hOutput, EM_GETLINECOUNT, 0, 0) - SendMessage(hOutput, EM_GETFIRSTVISIBLELINE, 0, 0));
                break;
            
            case EDIT_RECORD:
                DisplayEditDialog(hWnd);
                break;

            case DELETE_RECORD:
                DisplayDeletionDialog(hWnd);
                break;

            case STOCK_ADD:
                DisplayStockDialog(hWnd);
                break;

            case SELL_INV:
                DisplaySellDialog(hWnd);
                break;

            case SORT_RECORDS:
                LL.sortData(hWnd);
                break;

            case REFRESH_BUTTON:
                char RefOutput[180000];
                strcpy(RefOutput, ""); //Clears texts from previous iterations
                strcat(RefOutput, LL.printAll());
                SetWindowText(hOutput, RefOutput);
        }
        break;
    case WM_CREATE:
        AddMenus(hWnd);
        AddControls(hWnd);
        break;
    case WM_CLOSE:
        DestroyWindow(hWnd);
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    }

    return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

void AddMenus(HWND hWnd)
{
    hMenu = CreateMenu();

    AppendMenu(hMenu, MF_STRING, EDIT_RECORD, "Edit Record");
    AppendMenu(hMenu, MF_STRING, DELETE_RECORD, "Delete Record");
    AppendMenu(hMenu, MF_STRING, STOCK_ADD, "Add Stock to Record");
    AppendMenu(hMenu, MF_STRING, SELL_INV, "Sell Inventory");
    AppendMenu(hMenu, MF_STRING, SORT_RECORDS, "Sort Records");
    SetMenu(hWnd, hMenu);
    cout << "Menus Added Successfully!" << endl;
}

void AddControls(HWND hWnd)
{

//Date
    CreateWindowEx(0, _T("Static"), _T("Date:"), WS_VISIBLE | WS_CHILD , 53, 43, 121, 47, hWnd,
    NULL, NULL, NULL);

    hDate = CreateWindowEx(0, _T("Edit"), _T(""), WS_VISIBLE | WS_CHILD | WS_BORDER | ES_AUTOHSCROLL, 53, 96, 121, 47, hWnd,
    NULL, NULL, NULL);

//Name
    CreateWindowEx(0, _T("Static"), _T("Item Name:"), WS_VISIBLE | WS_CHILD, 177, 43, 121, 47, hWnd,
    NULL, NULL, NULL);

    hName = CreateWindowEx(0, _T("Edit"), _T(""), WS_VISIBLE | WS_CHILD | WS_BORDER | ES_AUTOHSCROLL, 177, 96, 121, 47, hWnd,
    NULL, NULL, NULL);

//Quantity
    CreateWindowEx(0, _T("Static"), _T("Quantity:"), WS_VISIBLE | WS_CHILD, 302, 43, 121, 47, hWnd,
    NULL, NULL, NULL);

    hQty = CreateWindowEx(0, _T("Edit"), _T(""), WS_VISIBLE | WS_CHILD | WS_BORDER | ES_AUTOHSCROLL, 302, 96, 121, 47, hWnd,
    NULL, NULL, NULL);

//Price
    CreateWindowEx(0, _T("Static"), _T("Price:"), WS_VISIBLE | WS_CHILD, 426, 43, 121, 47, hWnd,
    NULL, NULL, NULL);

    hPrice = CreateWindowEx(0, _T("Edit"), _T(""), WS_VISIBLE | WS_CHILD | WS_BORDER | ES_AUTOHSCROLL, 426, 96, 121, 47, hWnd,
    NULL, NULL, NULL);
    
//BUTTON
    hButton = CreateWindowEx(0, _T("Button"), _T("ADD RECORD +"), WS_VISIBLE | WS_CHILD | ES_CENTER, 53, 150, 245, 50, hWnd, (HMENU)GENERATE_BUTTON, 
    NULL, NULL);

    hButton2 = CreateWindowEx(0, _T("Button"), _T("REFRESH DISPLAY"), WS_VISIBLE | WS_CHILD | ES_CENTER, 302, 150, 245, 50, hWnd, (HMENU)REFRESH_BUTTON, 
    NULL, NULL);

//TEXT BOX
    hOutput = CreateWindowEx(0, _T("Edit"), _T(""), 
    WS_VISIBLE | WS_CHILD | WS_BORDER | WS_VSCROLL | WS_HSCROLL | ES_MULTILINE | ES_READONLY | ES_AUTOVSCROLL | ES_LEFT | ES_AUTOHSCROLL,
    50, 225, 500, 235, hWnd, NULL, NULL, NULL);

    cout << "Controls Added Successfully!" << endl;
}

Window::Window()
    : m_hInstance(GetModuleHandle(nullptr))
{
    const TCHAR* CLASS_NAME = _T("Andrew Window Class");

    WNDCLASS wndClass = {};
    wndClass.lpszClassName = CLASS_NAME;
    wndClass.hInstance = m_hInstance;
    wndClass.hbrBackground = (HBRUSH) COLOR_WINDOW;
    wndClass.hIcon = LoadIcon(NULL, IDI_WINLOGO);
    wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
    wndClass.lpfnWndProc = WindowProc;

    if (RegisterClass(&wndClass) == 0)
    {
        DWORD error = GetLastError();
        if (error != ERROR_CLASS_ALREADY_EXISTS)
        {
            // Display an error message only if it's not due to the class already existing
            MessageBox(nullptr, _T("Window Registration Failed!"), _T("Error"), MB_ICONERROR | MB_OK);
        }
        return;
    }
    RegisterEditDialogClass(m_hInstance);
    RegisterDeletionDialogClass(m_hInstance);
    RegisterStockDialogClass(m_hInstance);
    RegisterSellDialogClass(m_hInstance);

    DWORD style = WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU | WS_MAXIMIZEBOX;

    RECT rect;
    rect.left = 250;
    rect.top = 250;
    rect.right = rect.left + width;
    rect.bottom = rect.top + height;

    AdjustWindowRect(&rect, style, false);

    m_hWnd = CreateWindowEx(0, 
        CLASS_NAME, "Inventory Management System", style, 
        rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top, NULL, NULL, m_hInstance, NULL);

    ShowWindow(m_hWnd, SW_SHOW);
}

Window::~Window()
{;
    const TCHAR* CLASS_NAME = _T("Andrew Window Class");

    UnregisterClass(CLASS_NAME, m_hInstance);
}

bool Window::ProcessMessages()
{
    MSG msg = {};

    while (PeekMessage(&msg, nullptr, 0u, 0u, PM_REMOVE))
    {
        if (msg.message == WM_QUIT)
        {
            return false;
        }

        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return true;
}

LRESULT CALLBACK DialogProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch(uMsg)
    {
        case WM_COMMAND:
            switch (wParam)
            {
            case DISPLAY_RECORD:
                char Records[50000];
                strcpy(Records, LL.printAll());
                SetWindowText(hDisplayInv, Records);
                break;
            case CONFIRM_EDIT:
                char Index[100], Choice[10], NewData[5000];
                GetWindowText(hIndex, Index, 100);
                GetWindowText(hEditWhich, Choice, 10);
                GetWindowText(hEditedData, NewData, 5000);

                if (strcmp(Index, "") == 0 || strcmp(Choice, "") == 0 || strcmp(NewData, "") == 0)
                {
                    Val = MessageBox(hWnd, "All fields are Not Complete!", "ERROR!",
                    MB_OK | MB_ICONWARNING);
                    if (Val == IDOK)
                    {return 0;}
                } else if (isdigit(Index[0]) && isdigit(Choice[0]))
                {
                    int intIndex = atoi(Index);
                    int intChoice = atoi(Choice);
                    string STR_NewData = NewData;
                    LL.replaceValue(intIndex, STR_NewData, intChoice, hWnd);
                } else
                {
                    Val = MessageBox(hWnd, "Please Enter in Digits in 1st and 2nd Input Boxes!", "INVALID TYPE", MB_OK | MB_ICONWARNING);
                    if (Val == IDOK)
                    {return 0;}
                }
                break;

            case CONFIRM_DELETION:
                char IndtoDelete[1000];
                GetWindowText(hDelete, IndtoDelete, 1000);
                if (strcmp(IndtoDelete, "") == 0)
                {
                    Val = MessageBox(hWnd, "All Fields are Not Complete!", "ERROR!",
                    MB_OK | MB_ICONWARNING);
                    if (Val == IDOK)
                    {return 0;}
                } else if (isdigit(IndtoDelete[0]))
                {
                    int TrueIndtoDelete = atoi(IndtoDelete);
                    LL.deleteNode(TrueIndtoDelete, hWnd);
                } else {
                    Val = MessageBox(hWnd, "Please Enter in Digits!", "INVALID TYPE", MB_OK | MB_ICONWARNING);
                    if (Val == IDOK)
                    {break;}
                }
                break;
            }
            break;
        case WM_CLOSE:
            EnableWindow(var.m_hWnd, true);
            DestroyWindow(hWnd);
            break;
        default:
            return DefWindowProc(hWnd, uMsg, wParam, lParam);
    }
    return DefWindowProc(hWnd, uMsg, wParam, lParam);
}


void RegisterEditDialogClass(HINSTANCE hInstance)
{
    const TCHAR* CLASS_NAME = _T("myEditDialog");
    
    WNDCLASS DialogEClass = {};

    DialogEClass.lpszClassName = CLASS_NAME;
    DialogEClass.hInstance = hInstance; 
    DialogEClass.hbrBackground = (HBRUSH) COLOR_WINDOW;
    DialogEClass.hIcon = LoadIcon(NULL, IDI_WINLOGO);
    DialogEClass.hCursor = LoadCursor(NULL, IDC_CROSS);
    DialogEClass.lpfnWndProc = DialogProc;

    RegisterClass(&DialogEClass);
}

void RegisterDeletionDialogClass(HINSTANCE hInstance)
{
    const TCHAR* CLASS_NAME = _T("myDeletionDialog");
    
    WNDCLASS DialogDClass = {};

    DialogDClass.lpszClassName = CLASS_NAME;
    DialogDClass.hInstance = hInstance; 
    DialogDClass.hbrBackground = (HBRUSH) COLOR_WINDOW;
    DialogDClass.hIcon = LoadIcon(NULL, IDI_WINLOGO);
    DialogDClass.hCursor = LoadCursor(NULL, IDC_CROSS);
    DialogDClass.lpfnWndProc = DialogProc;

    RegisterClass(&DialogDClass);
}

void DisplayEditDialog(HWND hWnd)
{
    hDlg = CreateWindowEx(0, _T("myEditDialog"),_T("Edit Record"), WS_VISIBLE | WS_OVERLAPPEDWINDOW, 
    250, 250, width+10, height+15, hWnd, NULL, NULL, NULL);

        hDisplayInv = CreateWindowEx(0, _T("Edit"), _T(""), 
        WS_VISIBLE | WS_CHILD | WS_BORDER | WS_VSCROLL | WS_HSCROLL | ES_MULTILINE | ES_READONLY | ES_AUTOVSCROLL | ES_LEFT | ES_AUTOHSCROLL,
        16, 28, 568, 140, hDlg, NULL, NULL, NULL);

        hDispButton = CreateWindowEx(0, _T("Button"), _T("Display Record"), WS_VISIBLE | WS_CHILD | ES_CENTER, 210, 177, 181, 20, hDlg, (HMENU)DISPLAY_RECORD, 
        NULL, NULL);

        CreateWindowEx(0, _T("Static"), _T("Which Index Should be Edited?:"), WS_VISIBLE | WS_CHILD | ES_LEFT, 16, 206, 222, 34, hDlg,
        NULL, NULL, NULL);

        hIndex = CreateWindowEx(0, _T("Edit"), _T(""), WS_VISIBLE | WS_CHILD | WS_BORDER | ES_AUTOHSCROLL, 248, 206, 336, 34, hDlg,
        NULL, NULL, NULL);

        CreateWindowEx(0, _T("Static"), _T("What Do You Want To Change? :\n1. Date\n2. Name\n3. Quantity\n4. Price"), 
        WS_VISIBLE | WS_CHILD | ES_LEFT, 16, 250, 222, 117, hDlg, NULL, NULL, NULL);

        hEditWhich= CreateWindowEx(0, _T("Edit"), _T(""), WS_VISIBLE | WS_CHILD | WS_BORDER | ES_AUTOHSCROLL, 248, 250, 336, 117, hDlg,
        NULL, NULL, NULL);

        CreateWindowEx(0, _T("Static"), _T("Input New Data: "), WS_VISIBLE | WS_CHILD | ES_LEFT, 16, 377, 222, 34, hDlg, NULL, NULL, NULL);

        hEditedData= CreateWindowEx(0, _T("Edit"), _T(""), WS_VISIBLE | WS_CHILD | WS_BORDER | ES_AUTOHSCROLL, 248, 377, 336, 34, hDlg,
        NULL, NULL, NULL);

        DlgButton = CreateWindowEx(0, _T("Button"), _T("Confirm Inputs"), WS_VISIBLE | WS_CHILD | ES_CENTER, 200, 422, 200, 50, hDlg, (HMENU)CONFIRM_EDIT, NULL, NULL);
        SendMessage(DlgButton, BM_SETIMAGE, IMAGE_BITMAP, 0);

    EnableWindow(var.m_hWnd, false);
    std::cout << "Dislplayed Edit Dialog Successfully!" << std::endl;
}

void DisplayDeletionDialog(HWND hWnd)
{
    hDlg2 = CreateWindowEx(0, _T("myDeletionDialog"),_T("Delete Record"), WS_VISIBLE | WS_OVERLAPPEDWINDOW, 
    250, 250, width+10, height+15, hWnd, NULL, NULL, NULL);

        hDisplayInv = CreateWindowEx(0, _T("Edit"), _T(""), 
        WS_VISIBLE | WS_CHILD | WS_BORDER | WS_VSCROLL | WS_HSCROLL | ES_MULTILINE | ES_READONLY | ES_AUTOVSCROLL | ES_LEFT | ES_AUTOHSCROLL,
        16, 28, 568, 190, hDlg2, NULL, NULL, NULL);

        hDispButton = CreateWindowEx(0, _T("Button"), _T("Display Record"), WS_VISIBLE | WS_CHILD | ES_CENTER, 210, 225, 181, 30, hDlg2, (HMENU) DISPLAY_RECORD, 
        NULL, NULL);

        CreateWindowEx(0, _T("Static"), _T("Which Index Should be Deleted?:"), WS_VISIBLE | WS_CHILD | ES_LEFT, 16, 280, 222, 34, hDlg2,
        NULL, NULL, NULL);

        hDelete = CreateWindowEx(0, _T("Edit"), _T(""), WS_VISIBLE | WS_CHILD | WS_BORDER | ES_AUTOHSCROLL, 248, 280, 336, 34, hDlg2,
        NULL, NULL, NULL);

        CreateWindowEx(0, _T("Button"), _T("Confirm Input"), WS_VISIBLE | WS_CHILD | ES_CENTER, 200, 350, 200, 60, hDlg2, (HMENU)CONFIRM_DELETION, NULL, NULL);

    EnableWindow(var.m_hWnd, false);
    std::cout << "Dislplayed Deletion Dialog Successfully!" << std::endl;
}
