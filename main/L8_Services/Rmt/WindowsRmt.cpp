#include "WindowsRmt.hpp"
#include "../../L7_WindowsGdi/GdiSimulator.hpp"
#include "Windows.h"

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
    // This is the location where a WM Post message to Windows would be in place.
    // However, this overfloods the GDI, so it is handled inside GdiSimulator.
    return true;
}

bool WindowsRmt::TxWaitAllDone()
{
    return true;
}
