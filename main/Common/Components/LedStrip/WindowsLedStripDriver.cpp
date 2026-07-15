#include "WindowsLedStripDriver.hpp"
#include <Windows.h>
#include "../../../Windows/GdiSimulator.hpp"

extern SimulatorContext _simulatorContext;

WindowsLedStripDriver::WindowsLedStripDriver()
    : _numberOfLeds(0)
{
}

void WindowsLedStripDriver::Send(const LedStripModel::Pixel* buffer, uint16_t count)
{
    _bufferLastSent.assign(buffer, buffer + count);
    PostMessage(_simulatorContext.hwndMain, WM_LEDSTRIP_UPDATE, 0, 0);
}
