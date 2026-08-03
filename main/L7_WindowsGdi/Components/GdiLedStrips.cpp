#include "GdiLedStrips.hpp"
#include "../../L5_DeviceModels/Ws28xx/Ws28xxDeviceModel.hpp"
#include "../../L9_Utilities/Log/Log.hpp"
#include "windows.h"
#include <algorithm>

const int LENGTH = 500;
const int WIDTH = 15; // Per led strip

GdiLedStrips::GdiLedStrips(
    uint16_t numberOfLedStrips,
    uint16_t ledsPerLedStrip,
    uint16_t x,
    uint16_t y,
    Ws28xxDeviceModel& ws28xxDeviceModel)
:   _numberOfLedStrips(numberOfLedStrips),
    _ledsPerLedStrip(ledsPerLedStrip),
    _x(x),
    _y(y),
    _ws28xxDeviceModel(ws28xxDeviceModel)
{
    _ledBackgroundBrush = CreateSolidBrush(RGB(64, 64, 64));
}

GdiLedStrips::~GdiLedStrips()
{
    DeleteObject(_ledBackgroundBrush);
}

int GdiLedStrips::D(
    int value)
{
    return value * 2;
}

/// @brief Updates the LEDs with the leds according to the device model.
/// Note although the convention that the left bottom led is coordinate (0, 0) it seems it starts from the left top.
/// The reason is that the orientation is default vertical so the left side is the 'bottom', and then the left corner is
/// coordinate (0, 0).
/// @param hdc 
void GdiLedStrips::Update(
    HDC* hdc)
{
    // Draw the LED strips background
    for (int ledStripIndex = 0; ledStripIndex < 5; ledStripIndex++)
    {
        RECT rectMain{ _x - 5, _y + D(ledStripIndex * WIDTH), _x + D(LENGTH + 10), _y + D((ledStripIndex + 1) * WIDTH) };
        FillRect(*hdc, &rectMain, _ledBackgroundBrush);
    }

    uint16_t ledIndex = 0;
    auto* leds = _ws28xxDeviceModel.GetLeds();
    for (int ledIndex = 0; ledIndex < _ws28xxDeviceModel.GetNrOfLeds(); ledIndex++)
    {
        auto led = leds[ledIndex];

        int ledStripIndex = ledIndex / 72;
        int ledPositionInStrip = ledIndex % 72;
        if (ledStripIndex % 2 == 1)
        {
            ledPositionInStrip = 72 - 1 - ledPositionInStrip; // Reverse the order for odd strips
        }
        HBRUSH brushLed = CreateSolidBrush(RGB(led.red, led.green, led.blue));
        
        //HBRUSH brushLedForCircle = CreateSolidBrush(RGB(led.red, led.green, led.blue));
        HBRUSH oldBrush = (HBRUSH)SelectObject(*hdc, brushLed);

        // compute rect boundaries
        int left = _x + D(ledPositionInStrip * 7);
        int top = _y + D(ledStripIndex * WIDTH);
        int right = _x + D((ledPositionInStrip + 1) * 7) - 2;
        int bottom = _y + D((ledStripIndex + 1) * WIDTH) - 2;

        // convert rect → circle
        int cx = (left + right) / 2;
        int cy = (top + bottom) / 2;
        int radius = ((right - left) < (bottom - top)
            ? (right - left)
            : (bottom - top)) / 2;
        radius += 1;

        // draw circle
        Ellipse(*hdc, cx - radius, cy - radius, cx + radius, cy + radius);

        // cleanup
        SelectObject(*hdc, oldBrush);

        DeleteObject(brushLed);
    }
}
