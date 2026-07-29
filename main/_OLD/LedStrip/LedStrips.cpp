#include "LedStrips.hpp"

LedStrips::LedStrips(Ws28xxDeviceModel& ws28xxDeviceModel)
: _orientation(Horizontal), _ws28xxDeviceModel(ws28xxDeviceModel)
{
}


const Ws28xxDeviceModel::Pixel LedStrips::GetPixel(uint8_t x, uint8_t y) const
{
    uint16_t ledIndex = GetLedIndex(x, y);
    return _ws28xxDeviceModel.GetPixel(ledIndex);
}

void LedStrips::SetPixel(uint8_t x, uint8_t y, uint8_t red, uint8_t green, uint8_t blue)
{
    uint16_t ledIndex = GetLedIndex(x, y);

    if (ledIndex >= NUMBER_OF_LEDS)
        return;

    _ws28xxDeviceModel.SetPixel(ledIndex, red, green, blue);
}

void LedStrips::Fill(uint8_t red, uint8_t green, uint8_t blue)
{
    _ws28xxDeviceModel.Fill(red, green, blue);
}
