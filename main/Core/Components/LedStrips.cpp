#include "LedStrips.hpp"

LedStrips::LedStrips()
:     _buffer {}, _orientation(EOrientation::Horizontal)
{
}

void LedStrips::SetPixel(uint16_t index, uint8_t r, uint8_t g, uint8_t b)
{
    if (index < NumberOfLeds)
    {
        _buffer[index] = { r, g, b };
    }
}

void LedStrips::Fill(uint8_t r, uint8_t g, uint8_t b)
{
    for (auto& px : _buffer)
    {
        px = { r, g, b };
    }
}

const LedStrips::Pixel* LedStrips::GetBuffer() const
{
    return _buffer;
}

LedStrips::Pixel LedStrips::GetPixel(uint16_t index)
{
    return _buffer[index];
}

void LedStrips::SetOrientation(EOrientation orientation) 
{
    _orientation = orientation; 
}