#pragma once

#include <windows.h>

struct SimulatorContext
{
    HWND hwndMain;
};

#define WM_LEDSTRIP_UPDATE (WM_USER + 1)

