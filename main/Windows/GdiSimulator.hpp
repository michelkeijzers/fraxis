#pragma once

#include <cstdint>
#include <windows.h>

struct SimulatorContext
{
    HWND hwndMain;
};

const uint32_t WM_LED_STRIP_UPDATE          = (WM_USER + 1);
const uint32_t WM_LCD_1602_DISPLAY_UPDATE   = (WM_USER + 2);
