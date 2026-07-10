#include "WindowsLedStripDriver.hpp"

WindowsLedStripDriver::WindowsLedStripDriver()
    : _numberOfLeds(0)
{
}

void WindowsLedStripDriver::Send(const LedStripModel::Pixel* buffer, uint16_t count)
{
    _bufferLastSent.assign(buffer, buffer + count);
}
