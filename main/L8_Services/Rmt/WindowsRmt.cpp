#include "WindowsRmt.hpp"
#include "../../L7_WindowsGdi/GdiSimulator.hpp"
#include "windows.h"

WindowsRmt::WindowsRmt()
{}

WindowsRmt::~WindowsRmt()
{}

bool WindowsRmt::DelEncoder()
{
    return true;
}

bool WindowsRmt::DelChannel()
{
    return true;
}

bool WindowsRmt::NewTxChannel(
    uint8_t pin)
{
    return true;
}

bool WindowsRmt::Enable()
{
    return true;
}

bool WindowsRmt::NewSimpleEncoder()
{
    return true;
}

bool WindowsRmt::Transmit(
    const void* payload, 
    size_t payload_bytes)
{
    PostMessage(simulatorContext.hWndMain, WM_LED_STRIP_UPDATE, 0, 0);
    return true;
}

bool WindowsRmt::TxWaitAllDone()
{
    return true;
}
