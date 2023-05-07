#include <windows.h>

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    // Register window class
    const char* CLASS_NAME = "MyWindowClass";
    WNDCLASS wc = {};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;
    RegisterClass(&wc);

    // Create window
    HWND hwnd = CreateWindow(CLASS_NAME, "My Window", WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, 1920, 1080, NULL, NULL, hInstance, NULL);

    // Create buttons
    HWND button1 = CreateWindow("BUTTON", "FCFS ADD", WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
        10, 10, 100, 30, hwnd, NULL, hInstance, NULL);
    HWND button2 = CreateWindow("BUTTON", "Priority Scheduling ADD", WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
        120, 10, 100, 30, hwnd, NULL, hInstance, NULL);
    HWND button3 = CreateWindow("BUTTON", "List Processes FSFS Add", WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
        230, 10, 100, 30, hwnd, NULL, hInstance, NULL);
    HWND button4 = CreateWindow("BUTTON", "List Processes PS Add", WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
        340, 10, 100, 30, hwnd, NULL, hInstance, NULL);
    HWND button5 = CreateWindow("BUTTON", "Run Button", WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
        450, 10, 100, 30, hwnd, NULL, hInstance, NULL);

    // Show window
    ShowWindow(hwnd, nCmdShow);

    // Main message loop
    MSG msg = {};
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}
