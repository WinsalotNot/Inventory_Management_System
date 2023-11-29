#include <iostream>
#include "WindowsAPI.h"
using namespace std;

int main()
{
    cout << "Creating Window...\n";

    Window* pWindow = new Window();

    bool running = true;
    while (running)
    {
        if (!pWindow->ProcessMessages())
        {
            cout << "Closing Window...\n";
            running = false;
        }

        Sleep(10);
    }

    delete pWindow;

    return 0;
}