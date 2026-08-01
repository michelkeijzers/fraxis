#pragma once

#include <cstdint>
#include <windows.h>

struct SimulatorContext
{
    HWND hWndMain;
};

extern SimulatorContext simulatorContext;

const uint32_t WM_I2C_MASTER_WRITE_TO_DEVICE    = (WM_USER + 1);
