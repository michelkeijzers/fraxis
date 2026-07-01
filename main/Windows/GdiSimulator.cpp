// GdiSimulator.cpp : Defines the entry point for the application.
//

// #include "framework.h"
#include "GdiSimulator.hpp"
#include "GdiScreen.hpp"
#include "../Windows/Components/WindowsLcd1602Display.hpp"
#include "../Windows/Components/WindowsMcp23017.hpp"
#include "../Core/Menu/MenuSimulator.hpp"
#include "../Core/Menu/MenuInput.hpp"
#include "windowsx.h"
#include "IGdiMouseInput.hpp"
#include "../Core/Components/PinIo.hpp"

#define MAX_LOADSTRING 100

WindowsLcd1602Display windowsLcd1602Display;
WindowsMcp23017 windowsMcp23017;
PinIo pinIo(windowsMcp23017);
MenuSimulator menuSimulator(windowsLcd1602Display, pinIo);
GdiScreen gdiScreen(pinIo, windowsLcd1602Display, menuSimulator);


// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Place code here.

    // Initialize global strings
    //LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    //LoadStringW(hInstance, IDC_GDISIMULATOR, szWindowClass, MAX_LOADSTRING);
	 wcscpy_s(szWindowClass, L"GdiSimulatorWindowClass");
	 wcscpy_s(szTitle, L"GDI Simulator");

    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    // HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_GDISIMULATOR));

    MSG msg;

    // Main message loop:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, 0, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}

//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEXW wcex{};
	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;

	// Use default system icons (no resource file needed)
	wcex.hIcon = LoadIcon(nullptr, IDI_APPLICATION);
	wcex.hIconSm = LoadIcon(nullptr, IDI_APPLICATION);

	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);

	// No menu (your simulator doesn’t use menus)
	wcex.lpszMenuName = nullptr;

	// Your window class name
	wcex.lpszClassName = L"GdiSimulatorWindowClass";

	return RegisterClassExW(&wcex);
}


//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Store instance handle in our global variable

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

	RECT rc;
	GetClientRect(hWnd, &rc);
	gdiScreen.CreateMemoryDc(hWnd, rc.right - rc.left, rc.bottom - rc.top);

	SetTimer(hWnd, 1, 10, NULL);   // 10 ms timer


   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE: Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
   {
	case WM_MOUSEMOVE:
	{
		int mx = GET_X_LPARAM(lParam);
		int my = GET_Y_LPARAM(lParam);

		gdiScreen.OnMouseMove(mx, my);
		InvalidateRect(hWnd, NULL, FALSE);
	}
	break;

	case WM_LBUTTONDOWN:
	{
		int mx = GET_X_LPARAM(lParam);
		int my = GET_Y_LPARAM(lParam);

		gdiScreen.OnMouseDown(mx, my);
		InvalidateRect(hWnd, NULL, FALSE);
	}
	break;

	case WM_LBUTTONUP:
	{
		int mx = GET_X_LPARAM(lParam);
		int my = GET_Y_LPARAM(lParam);

		gdiScreen.OnMouseUp(mx, my);
		InvalidateRect(hWnd, NULL, FALSE);
	}
	break;

	case WM_KEYDOWN:
		{
			switch (wParam)
			{
			case VK_ESCAPE:    menuSimulator.GetMenuInput().SetSystemButtonState(true); break;
			
			case VK_SPACE:   menuSimulator.GetMenuInput().SetJoystickState(AtariJoystick::EId::Player1, (uint8_t)AtariJoystick::EItem::Button); break;
			case VK_UP:      menuSimulator.GetMenuInput().SetJoystickState(AtariJoystick::EId::Player1, (uint8_t)AtariJoystick::EItem::Up); break;
			case VK_DOWN:    menuSimulator.GetMenuInput().SetJoystickState(AtariJoystick::EId::Player1, (uint8_t)AtariJoystick::EItem::Down); break;
			case VK_LEFT:    menuSimulator.GetMenuInput().SetJoystickState(AtariJoystick::EId::Player1, (uint8_t)AtariJoystick::EItem::Left); break;
			case VK_RIGHT:   menuSimulator.GetMenuInput().SetJoystickState(AtariJoystick::EId::Player1, (uint8_t)AtariJoystick::EItem::Right); break;

			case VK_NUMPAD5: menuSimulator.GetMenuInput().SetJoystickState(AtariJoystick::EId::Player2, (uint8_t)AtariJoystick::EItem::Button); break;
			case VK_NUMPAD8: menuSimulator.GetMenuInput().SetJoystickState(AtariJoystick::EId::Player2, (uint8_t)AtariJoystick::EItem::Up); break;
			case VK_NUMPAD2: menuSimulator.GetMenuInput().SetJoystickState(AtariJoystick::EId::Player2, (uint8_t)AtariJoystick::EItem::Down); break;
			case VK_NUMPAD4: menuSimulator.GetMenuInput().SetJoystickState(AtariJoystick::EId::Player2, (uint8_t)AtariJoystick::EItem::Left); break;
			case VK_NUMPAD6: menuSimulator.GetMenuInput().SetJoystickState(AtariJoystick::EId::Player2, (uint8_t)AtariJoystick::EItem::Right); break;
			}
		}
		break;
		void SetJoystickState(GdiAtariJoystick::EId joystickId, uint8_t pressedItems);
	case WM_KEYUP:
		menuSimulator.GetMenuInput().SetSystemButtonState(false);
		menuSimulator.GetMenuInput().SetJoystickState(AtariJoystick::EId::Player1, (uint8_t)0);
		menuSimulator.GetMenuInput().SetJoystickState(AtariJoystick::EId::Player2, (uint8_t)0);
		break;

   case WM_PAINT:
        {
			 PAINTSTRUCT ps;
          HDC hdc = BeginPaint(hWnd, &ps);

			 RECT rc;
			 GetClientRect(hWnd, &rc);
			 BitBlt(hdc, 0, 0, rc.right - rc.left, rc.bottom - rc.top, gdiScreen.GetMemDC(), 0, 0, SRCCOPY);
			 EndPaint(hWnd, &ps);
        }
        break;

	 case WM_ERASEBKGND:
		 return 1; // Prevent flickering by not erasing the background

	 case WM_TIMER:
		 gdiScreen.GetLedStrips().SetLed((GetTickCount64() / 10) % 360, 
			 GetTickCount64() % 255, 
			 (GetTickCount64() / 5) % 255, 
			 (GetTickCount64() / 8) % 255);
		 menuSimulator.run();
		 gdiScreen.Update();
 		 InvalidateRect(hWnd, NULL, FALSE); // request redraw
		 break;

    case WM_DESTROY:
        PostQuitMessage(0);
        break;

	 default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}

