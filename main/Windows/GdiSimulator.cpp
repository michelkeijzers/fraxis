// GdiSimulator.cpp : Defines the entry point for the application.

#include "GdiSimulator.hpp"
#include "windowsx.h"
#include "IGdiMouseInput.hpp"
#include "../Windows/GdiScreen.hpp"
#include "../Common/Services/RtosTask/WindowsRtosTask.hpp"
#include "../Common/Services/RtosQueue/WindowsRtosQueue.hpp"
#include "../Common/Components/LedStrip/WindowsLedStripDriver.hpp"
#include "../Common/Components/Lcd1602Display/WindowsLcd1602DisplayDriver.hpp"
#include "../Common/Components/Tm1637/WindowsTm1637Driver.hpp"
#include "../common/Components/Mcp23017/WindowsMcp23017.hpp"
#include "../Core/TaskManager/TaskManager.hpp"
#include "../Windows/Components/WindowsComponentsBuilder.hpp"

TaskManager* _taskManager;
GdiScreen* _gdiScreen;

WindowsComponentsBuilder::Drivers _drivers;

SimulatorContext _simulatorContext;

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(
	_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR    lpCmdLine,
    _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    WindowsComponentsBuilder windowsComponentsBuilder;
    windowsComponentsBuilder.Build();

    _drivers = windowsComponentsBuilder.GetDrivers();
    _taskManager = new TaskManager(windowsComponentsBuilder.GetFraxisComponents(),
        windowsComponentsBuilder.GetModels(), _drivers);

    _gdiScreen = new GdiScreen(
        windowsComponentsBuilder.GetModels().ledStripModel,
        windowsComponentsBuilder.GetModels().lcd1602DisplayModel,
        windowsComponentsBuilder.GetModels().tm1637ModelCentralPanel,
        windowsComponentsBuilder.GetModels().tm1637ModelPlayer1,
        windowsComponentsBuilder.GetModels().tm1637ModelPlayer2,
        windowsComponentsBuilder.GetFraxisComponents().pinIo,
        dynamic_cast<WindowsMcp23017*>(windowsComponentsBuilder.GetDrivers().mcp23017)
    );

    _taskManager->Initialize();
    _taskManager->Run(false);

	wcscpy_s(szWindowClass, L"GdiSimulatorWindowClass");
	wcscpy_s(szTitle, L"GDI Simulator");

    MyRegisterClass(hInstance);
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    MSG msg;
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return (int) msg.wParam;
}

ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEXW wcex{};
	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;

	wcex.hIcon = LoadIcon(nullptr, IDI_APPLICATION);
	wcex.hIconSm = LoadIcon(nullptr, IDI_APPLICATION);

	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);

	wcex.lpszMenuName = nullptr;

	wcex.lpszClassName = L"GdiSimulatorWindowClass";

	return RegisterClassExW(&wcex);
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
    hInst = hInstance; // Store instance handle in our global variable

    HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);
    _simulatorContext.hwndMain = hWnd;

    if (!hWnd)
    {
        return FALSE;
    }

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

	RECT rc;
	GetClientRect(hWnd, &rc);
	_gdiScreen->CreateMemoryDc(hWnd, rc.right - rc.left, rc.bottom - rc.top);

	SetTimer(hWnd, 1, 1, NULL);   // 1 ms timer
    return TRUE;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
    case WM_LED_STRIP_UPDATE:
        _gdiScreen->UpdateLedStrips();
        break;

    case WM_LCD_1602_DISPLAY_UPDATE:
        _gdiScreen->UpdateLcd1602Display();
        break;

    case WM_TM1637_UPDATE:
        _gdiScreen->UpdateTm1637();
        break;

    case WM_MOUSEMOVE:
	{
		int mx = GET_X_LPARAM(lParam);
		int my = GET_Y_LPARAM(lParam);

		_gdiScreen->OnMouseMove(mx, my);
		InvalidateRect(hWnd, NULL, FALSE);
	}
	break;

	case WM_LBUTTONDOWN:
	{
		int mx = GET_X_LPARAM(lParam);
		int my = GET_Y_LPARAM(lParam);

		_gdiScreen->OnMouseDown(mx, my);
		InvalidateRect(hWnd, NULL, FALSE);
	}
	break;

	case WM_LBUTTONUP:
	{
		int mx = GET_X_LPARAM(lParam);
		int my = GET_Y_LPARAM(lParam);

		_gdiScreen->OnMouseUp(mx, my);
		InvalidateRect(hWnd, NULL, FALSE);
	}
	break;

	case WM_KEYDOWN:
		{
        WindowsMcp23017* mcp23017 = dynamic_cast<WindowsMcp23017*>(_drivers.mcp23017);
			switch (wParam)
			{
			case VK_ESCAPE:  mcp23017->SimulateSetGpioPin(PinIoMappings::EIdBit::SystemButton  , 1); break;
			case VK_SPACE:   mcp23017->SimulateSetGpioPin(PinIoMappings::EIdBit::Player1Button , 1); break;
			case VK_UP:      mcp23017->SimulateSetGpioPin(PinIoMappings::EIdBit::Player1Up     , 1); break;
			case VK_DOWN:    mcp23017->SimulateSetGpioPin(PinIoMappings::EIdBit::Player1Down   , 1); break;
			case VK_LEFT:    mcp23017->SimulateSetGpioPin(PinIoMappings::EIdBit::Player1Left   , 1); break;
			case VK_RIGHT:   mcp23017->SimulateSetGpioPin(PinIoMappings::EIdBit::Player1Right  , 1); break;

			case VK_NUMPAD5: mcp23017->SimulateSetGpioPin(PinIoMappings::EIdBit::Player2Button , 1); break;
			case VK_NUMPAD8: mcp23017->SimulateSetGpioPin(PinIoMappings::EIdBit::Player2Up     , 1); break;
			case VK_NUMPAD2: mcp23017->SimulateSetGpioPin(PinIoMappings::EIdBit::Player2Down   , 1); break;
			case VK_NUMPAD4: mcp23017->SimulateSetGpioPin(PinIoMappings::EIdBit::Player2Left   , 1); break;
			case VK_NUMPAD6: mcp23017->SimulateSetGpioPin(PinIoMappings::EIdBit::Player2Right  , 1); break;
			}
		}
		break;

    case WM_KEYUP:
    {
        WindowsMcp23017* mcp23017 = dynamic_cast<WindowsMcp23017*>(_drivers.mcp23017);
        mcp23017->SimulateResetGpioPins();
    }
		break;

	case WM_PAINT:
        {
			PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);

			RECT rc;
			GetClientRect(hWnd, &rc);
			BitBlt(hdc, 0, 0, rc.right - rc.left, rc.bottom - rc.top, _gdiScreen->GetMemDC(), 0, 0, SRCCOPY);
			EndPaint(hWnd, &ps);
        }
        break;

	case WM_ERASEBKGND:
		 return 1; // Prevent flickering by not erasing the background

	case WM_TIMER:
		_gdiScreen->Update();
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
