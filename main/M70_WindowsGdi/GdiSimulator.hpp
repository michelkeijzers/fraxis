#pragma once

#include <cstdint>
#include <Windows.h>

namespace M70
{
    struct SimulatorContext
    {
        HWND hWndMain;
    };

    extern M70::SimulatorContext simulatorContext;

    const uint32_t WM_LCD2004_UPDATE = (WM_USER + 1);
    const uint32_t WM_MCP23017_OUTPUT_UPDATE = (WM_USER + 2);
    const uint32_t WM_TM1637_CENTRAL_PANEL_UPDATE = (WM_USER + 3);
    const uint32_t WM_TM1637_PLAYER1_UPDATE = (WM_USER + 4);
    const uint32_t WM_TM1637_PLAYER2_UPDATE = (WM_USER + 5);
}
