#include "WindowsHighResolutionTimer.hpp"

#include <windows.h>
#include <timeapi.h>
#pragma comment(lib, "winmm.lib")  // Link against winmm.lib

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
