/// @brief: GdiSimulator.cpp : Defines the entry point for the application.

#include "GdiSimulator.hpp"
#include "windowsx.h"
#include "IGdiMouseInput.hpp"
#include "GdiScreen.hpp"
#include "../L0_System/Orchestrator.hpp"
#include "../L1_Composition/Context/Context.hpp"
#include "../L1_Composition/Builder/WindowsBuilder.hpp"
#include "../L2_Applications/ApplicationsTask.hpp"
#include "../L0_System/DeviceSettings.hpp"
#include "../L9_Utilities/Log/Log.hpp"
#include "../L9_Utilities/Time/TimeUtilities.hpp"
#include "../L9_Utilities/Time/WindowsHighResolutionTimer.hpp"
#include <thread>

GdiScreen _gdiScreen;

SimulatorContext simulatorContext; // NOSONAR Cannot be made const @todo

static constexpr int MAX_LOADSTRING = 100;

// Global Variables:
HINSTANCE hInst;                                // current instance NOSONAR 
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text NOSONAR 
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name NOSONAR

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

    WindowsHighResolutionTimer timer;

    Context context;
    WindowsBuilder windowsBuilder(context);
    Orchestrator orchestrator(windowsBuilder);
    
    wcscpy_s(szWindowClass, L"GdiSimulatorWindowClass");
    wcscpy_s(szTitle, L"GDI Simulator");

    MyRegisterClass(hInstance);

    orchestrator.Initialize();
    _gdiScreen.SetDeviceModels(context.GetDeviceModels());
    _gdiScreen.SetDeviceDrivers(context.GetDeviceDrivers());

    if (!InitInstance(hInstance, nCmdShow))
    {
        return FALSE;
    }

    std::jthread orchestratorThread([&orchestrator]()
        {
            orchestrator.StartTasks();
        });

    MSG msg;
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    orchestratorThread.join();
    return (int)msg.wParam;
}

ATOM MyRegisterClass(
    HINSTANCE hInstance)
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

BOOL InitInstance(
    HINSTANCE hInstance, 
    int nCmdShow)
{
    hInst = hInstance; // Store instance handle in our global variable

    //int screenWidth = GetSystemMetrics(SM_CXSCREEN); // NOSONAR possible future use
    //int screenHeight = GetSystemMetrics(SM_CYSCREEN); // NOSONAR possible future use
    HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, 1150, 700, nullptr, nullptr, hInstance, nullptr);
    Assert::IsNotNullptr(hWnd, "hWnd");

    simulatorContext.hWndMain = hWnd;

    if (!hWnd)
    {
        return FALSE;
    }

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    RECT rc;
    GetClientRect(hWnd, &rc);
    _gdiScreen.CreateMemoryDc(hWnd, (uint16_t)(rc.right - rc.left), (uint16_t)(rc.bottom - rc.top));

    UINT_PTR timerResult = SetTimer(hWnd, 1, 17, nullptr);   // Arguments: hWnd, timer id, ms interval, parameters)
    Assert::IsNot0(timerResult, "Timer result");
    return TRUE;
}


void ProcessWmKeyDown(
    WPARAM wParam)
{
    switch (wParam)
    {
    case VK_ESCAPE:
        _gdiScreen.TriggerSystemButton(true);
        break;

    case VK_UP:
        _gdiScreen.TriggerJoystickSwitch(
            Types::EJoystickId::Player1, GdiAtariJoystick::ESwitchBitNumber::Up, true);
        break;

    case VK_RIGHT:
        _gdiScreen.TriggerJoystickSwitch(
            Types::EJoystickId::Player1, GdiAtariJoystick::ESwitchBitNumber::Right, true);
        break;

    case VK_DOWN:
        _gdiScreen.TriggerJoystickSwitch(
            Types::EJoystickId::Player1, GdiAtariJoystick::ESwitchBitNumber::Down, true);
        break;

    case VK_LEFT:
        _gdiScreen.TriggerJoystickSwitch(
            Types::EJoystickId::Player1, GdiAtariJoystick::ESwitchBitNumber::Left, true);
        break;

    case VK_SPACE:
        _gdiScreen.TriggerJoystickSwitch(
            Types::EJoystickId::Player1, GdiAtariJoystick::ESwitchBitNumber::Button, true);
        break;

    case VK_NUMPAD8:
        _gdiScreen.TriggerJoystickSwitch(
            Types::EJoystickId::Player2, GdiAtariJoystick::ESwitchBitNumber::Up, true);
        break;

    case VK_NUMPAD6:
        _gdiScreen.TriggerJoystickSwitch(
            Types::EJoystickId::Player2, GdiAtariJoystick::ESwitchBitNumber::Right, true);
        break;

    case VK_NUMPAD2:
        _gdiScreen.TriggerJoystickSwitch(
            Types::EJoystickId::Player2, GdiAtariJoystick::ESwitchBitNumber::Down, true);
        break;

    case VK_NUMPAD4:
        _gdiScreen.TriggerJoystickSwitch(
            Types::EJoystickId::Player2, GdiAtariJoystick::ESwitchBitNumber::Left, true);
        break;

    case VK_NUMPAD5:
        _gdiScreen.TriggerJoystickSwitch(
            Types::EJoystickId::Player2, GdiAtariJoystick::ESwitchBitNumber::Button, true);
        break;

    default:
        // Ignore other keys.
        break;
    }
}

void ProcessWmKeyUp(
    WPARAM wParam)
{
    switch (wParam)
    {
    case VK_ESCAPE:
        _gdiScreen.TriggerSystemButton(false);
        break;  

    case VK_UP:
        _gdiScreen.TriggerJoystickSwitch(
            Types::EJoystickId::Player1, GdiAtariJoystick::ESwitchBitNumber::Up, false);
        break;

    case VK_RIGHT:
        _gdiScreen.TriggerJoystickSwitch(
            Types::EJoystickId::Player1, GdiAtariJoystick::ESwitchBitNumber::Right, false);
        break;

    case VK_DOWN:
        _gdiScreen.TriggerJoystickSwitch(
            Types::EJoystickId::Player1, GdiAtariJoystick::ESwitchBitNumber::Down, false);
        break;

    case VK_LEFT:
        _gdiScreen.TriggerJoystickSwitch(
            Types::EJoystickId::Player1, GdiAtariJoystick::ESwitchBitNumber::Left, false);
        break;

    case VK_SPACE:
        _gdiScreen.TriggerJoystickSwitch(
            Types::EJoystickId::Player1, GdiAtariJoystick::ESwitchBitNumber::Button, false);
        break;

    case VK_NUMPAD8:
        _gdiScreen.TriggerJoystickSwitch(
            Types::EJoystickId::Player2, GdiAtariJoystick::ESwitchBitNumber::Up, false);
        break;

    case VK_NUMPAD6:
        _gdiScreen.TriggerJoystickSwitch(
            Types::EJoystickId::Player2, GdiAtariJoystick::ESwitchBitNumber::Right, false);
        break;

    case VK_NUMPAD2:
        _gdiScreen.TriggerJoystickSwitch(
            Types::EJoystickId::Player2, GdiAtariJoystick::ESwitchBitNumber::Down, false);
        break;

    case VK_NUMPAD4:
        _gdiScreen.TriggerJoystickSwitch(
            Types::EJoystickId::Player2, GdiAtariJoystick::ESwitchBitNumber::Left, false);
        break;

    case VK_NUMPAD5:
        _gdiScreen.TriggerJoystickSwitch(
            Types::EJoystickId::Player2, GdiAtariJoystick::ESwitchBitNumber::Button, false);
        break;

    default:
        // Ignore others
        break;
    }
}

LRESULT CALLBACK WndProc(
    HWND hWnd,
    UINT message,
    WPARAM wParam, 
    LPARAM lParam)
{
    switch (message)
    {
    case WM_CREATE:
        break;

    case WM_SHOWWINDOW:
        // No action needed.
        break;

        /// @todo: Future: resize according to actual window size.
    case WM_SIZE:
    {
        _gdiScreen.Update();
        InvalidateRect(hWnd, nullptr, FALSE);
    }
    break;

    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);

        RECT rc;
        GetClientRect(hWnd, &rc);
        BitBlt(hdc, 0, 0, rc.right - rc.left, rc.bottom - rc.top,
            _gdiScreen.GetMemDc(), 0, 0, SRCCOPY);
        EndPaint(hWnd, &ps);
    }
    break;

    case WM_ERASEBKGND:
        return 1; // Prevent flickering by not erasing the background

    case WM_TIMER:
    {
        if (wParam == 1) // Timer Id
        {
            // to prevent updating the LED strips for every LED Strip event which be 
            // hundreds every cycle, only update it when invalidating the GDI screen.
            //_gdiScreen->UpdateLedStrips();    
            _gdiScreen.Update(); /// @todo: update everything otherwise enclosure doesn't show (not sure why)
            InvalidateRect(hWnd, nullptr, FALSE);
        }
    }
    break;

    case WM_DESTROY:
        KillTimer(hWnd, 1);
        PostQuitMessage(0);
        break;

    case WM_LCD2004_UPDATE:
        _gdiScreen.UpdateLcd2004();
        break;

    case WM_MCP23017_OUTPUT_UPDATE:
        _gdiScreen.UpdateMcp23017Output();
        break;

    case WM_TM1637_CENTRAL_PANEL_UPDATE:
        _gdiScreen.UpdateTm1637CentralPanel();
        break;

    case WM_TM1637_PLAYER1_UPDATE:
        _gdiScreen.UpdateTm1637Player1();
        break;

    case WM_TM1637_PLAYER2_UPDATE:
        _gdiScreen.UpdateTm1637Player2();
        break;

    case WM_MOUSEMOVE:
    {
        auto mx = (uint16_t)GET_X_LPARAM(lParam);
        auto my = (uint16_t)GET_Y_LPARAM(lParam);
        _gdiScreen.OnMouseMove(mx, my);
    }
    break;

    case WM_LBUTTONDOWN:
    {
        auto mx = (uint16_t)GET_X_LPARAM(lParam);
        auto my = (uint16_t)GET_Y_LPARAM(lParam);
        _gdiScreen.OnMouseDown(mx, my);
    }
    break;

    case WM_LBUTTONUP:
    {
        auto mx = (uint16_t)GET_X_LPARAM(lParam);
        auto my = (uint16_t)GET_Y_LPARAM(lParam);
        _gdiScreen.OnMouseUp(mx, my);
    }
    break;

    case WM_KEYDOWN:
        ProcessWmKeyDown(wParam);
        break;

    case WM_KEYUP:
        ProcessWmKeyUp(wParam);
        break;

    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }

    return 0;
}
