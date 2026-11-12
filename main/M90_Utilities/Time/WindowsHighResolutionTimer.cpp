// @file WindowsHighResolutionTimer.cpp
// Copyright (c) 2026 Michel Keijzers
// SPDX-License-Identifier: GPL-3.0-only

#include "WindowsHighResolutionTimer.hpp"
#include <Windows.h>
#include <timeapi.h>
#pragma comment(lib, "winmm.lib")  // Link against winmm.lib

namespace M90::Time
{
    WindowsHighResolutionTimer::WindowsHighResolutionTimer()
    {
        // Request 1ms timer resolution
        timeBeginPeriod(1);
    }

    WindowsHighResolutionTimer::~WindowsHighResolutionTimer()
    {
        // Restore default timer resolution
        timeEndPeriod(1);
    }
}
