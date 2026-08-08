#include "GdiLedStrips.hpp"
#include "../../L4_DomainModels/LedStrips/LedStrips.hpp"
#include "../../L5_DeviceModels/Ws28xx/Ws28xxDeviceModel.hpp"
#include "../../L9_Utilities/Log/Log.hpp"
#include <Windows.h>
#include <algorithm>

const int LENGTH = 500;
const int WIDTH = 15; // Per led strip

GdiLedStrips::GdiLedStrips(
    uint16_t x,
    uint16_t y)
:   _x(x),
    _y(y)
{
    _ledBackgroundBrush = CreateSolidBrush(RGB(64, 64, 64));
    CreateBrushes();
}

GdiLedStrips::~GdiLedStrips()
{
    for (auto brush : _ledBrushes)
    {
        DeleteObject(brush);
    }

    DeleteObject(_ledBackgroundBrush);
}

Ws28xxDeviceModel& GdiLedStrips::GetDeviceModel()
{
    return *_deviceModel;
}

void GdiLedStrips::SetDeviceModel(
    Ws28xxDeviceModel& deviceModel)
{
    _deviceModel = &deviceModel;
}

void GdiLedStrips::CreateBrushes()
{
    uint8_t index = 0;

    for (uint8_t r = 0; r < 15; r++)
    {
        for (uint8_t g = 0; g < 15; g++)
        {
            for (uint8_t b = 0; b < 15; b++)
            {
                auto color = RGB(LEVELS[r], LEVELS[g], LEVELS[b]);
                _ledBrushes[index++] = CreateSolidBrush(color);
            }
        }
    }
}

uint16_t GdiLedStrips::D(
    uint16_t value) const
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
    for (uint16_t ledStripIndex = 0; ledStripIndex < LedStrips::NUMBER_OF_LED_STRIPS; ledStripIndex++)
    {
        RECT rectMain{ _x - 5, _y + D(ledStripIndex * WIDTH), _x + D(LENGTH + 10), _y + D((ledStripIndex + 1) * WIDTH) };
        FillRect(*hdc, &rectMain, _ledBackgroundBrush);
    }

    const uint16_t numberOfLedsPerLedStrip = LedStrips::NUMBER_OF_LEDS_PER_LED_STRIP;
    
    /// @details: See class details.
    auto* leds = GetDeviceModel().GetLeds();
    for (int ledIndex = 0; ledIndex < GetDeviceModel().GetNrOfLeds(); ledIndex++)
    {
        auto led = leds[ledIndex];

        int ledStripIndex = ledIndex / numberOfLedsPerLedStrip;
        int ledPositionInStrip = ledIndex % numberOfLedsPerLedStrip;
        if (ledStripIndex % 2 == 1)
        {
            ledPositionInStrip = numberOfLedsPerLedStrip - 1 - ledPositionInStrip; // Reverse the order for odd strips
        }
        HBRUSH& brushLed = FindBrush(led.red, led.green, led.blue);
        
        auto oldBrush = (HBRUSH)SelectObject(*hdc, brushLed);

        // compute rect boundaries
        uint16_t left = _x + D(ledPositionInStrip * 7); // NOSONAR: uint16_t is ok
        uint16_t top = _y + D(ledStripIndex * WIDTH); // NOSONAR: uint16_t is ok
        uint16_t right = _x + D((ledPositionInStrip + 1) * 7) - 2; // NOSONAR: uint16_t is ok
        uint16_t bottom = _y + D((ledStripIndex + 1) * WIDTH) - 2; // NOSONAR: uint16_t is ok

        // convert rect → circle
        uint16_t cx = (left + right) / 2; // NOSONAR: uint16_t is ok
        uint16_t cy = (top + bottom) / 2; // NOSONAR: uint16_t is ok
        uint16_t radius = ((right - left) < (bottom - top)
            ? (right - left)
            : (bottom - top)) / 2;
        radius += 1;

        // draw circle
        Ellipse(*hdc, cx - radius, cy - radius, cx + radius, cy + radius);

        // cleanup
        SelectObject(*hdc, oldBrush);
    }
}

HBRUSH& GdiLedStrips::FindBrush(uint8_t red, uint8_t green, uint8_t blue)
{
    // Quantize each channel to one of the 15 perceptual levels
    uint8_t qr = Quantize(red);
    uint8_t qg = Quantize(green);
    uint8_t qb = Quantize(blue);

    // Convert quantized RGB to brush index
    int index = BrushIndex(qr, qg, qb);

    // Return reference to pre-created brush
    return _ledBrushes[index];
}

uint8_t GdiLedStrips::Quantize(uint8_t colorLevel) const
{
    for (uint8_t colorIndex = 0; colorIndex < 15; colorIndex++)
        if (colorLevel <= LEVELS[colorIndex])
            return colorIndex;

    return 14; // last index
}

uint8_t GdiLedStrips::BrushIndex(
    uint8_t redIndex, 
    uint8_t greenIndex,
    uint8_t blueIndex) const
{
    return redIndex * 15 * 15 + greenIndex * 15 + blueIndex;
}