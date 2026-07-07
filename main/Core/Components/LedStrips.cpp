#include "LedStrips.hpp"

LedStrips::LedStrips()
:     _bufferA {}, _bufferB {}, _activeBuffer(_bufferA), _orientation(EOrientation::Horizontal)
{
}

void LedStrips::SetPixel(uint8_t x, uint8_t y, uint8_t red, uint8_t green, uint8_t blue)
{
    uint16_t index = CalculateLedIndex(x, y);
    if (index < NumberOfLeds)
    {
        _activeBuffer[index] = { red, green, blue };
    }
}

void LedStrips::Fill(uint8_t red, uint8_t green, uint8_t blue)
{
    for (uint16_t ledIndex = 0; ledIndex < NumberOfLeds; ++ledIndex)
    {
        _activeBuffer[ledIndex] = { red, green, blue };
    }
}

const LedStrips::Pixel* LedStrips::GetBuffer() const
{
    return _activeBuffer;
}

LedStrips::Pixel LedStrips::GetPixel(uint16_t index)
{
    return _activeBuffer[index];
}

void LedStrips::SetOrientation(EOrientation orientation) 
{
    _orientation = orientation; 
}

uint16_t LedStrips::CalculateLedIndex(uint8_t x, uint8_t y) const
{
    if (_orientation == EOrientation::Horizontal)
    {
        return y * NumberOfLedsPerLedStrip + x;
    }
    else
    {
        return x * NumberOfLedsPerLedStrip + y;
    }
}   