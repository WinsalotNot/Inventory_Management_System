#ifndef WINDOWSAPIH
#define WINDOWSAPIH
#include <windows.h>
#include <iostream>
#include "link_list.h"
#include "stack.h"
using namespace std;

void RegisterDeletionDialogClass(HINSTANCE hInstance);
void RegisterEditDialogClass(HINSTANCE hInstance);
void RegisterStockDialogClass(HINSTANCE hInstance);
void RegisterSellDialogClass(HINSTANCE hInstance);
void DisplayEditDialog(HWND hWnd);
void DisplayDeletionDialog(HWND hWnd);
void DisplayStockDialog(HWND hWnd);
void DisplaySellDialog(HWND hWnd);
LRESULT CALLBACK DialogProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

void AddMenus(HWND hWnd);
void AddControls(HWND hWnd);

class Window
{
public:
    HINSTANCE m_hInstance;
    HWND m_hWnd;
    Window();
    Window(const Window&) = delete;
    Window& operator =(const Window&) = delete;
    ~Window();

    bool ProcessMessages();
};

#endif