#include "Ws28xxDeviceModel.hpp"

Ws28xxDeviceModel::Ws28xxDeviceModel()
{
}

Ws28xxDeviceModel::~Ws28xxDeviceModel()
{
}

void Ws28xxDeviceModel::SetNrOfLeds(uint16_t nrOfLeds)
{
    _nrOfLeds = nrOfLeds;
}

/// @brief  Allocates memory for leds.
void Ws28xxDeviceModel::Initialize()
{
    _leds.reset(new rgb[_nrOfLeds]);
}

void Ws28xxDeviceModel::SetPixel(uint16_t index, uint8_t red, uint8_t green, uint8_t blue)
{
    _leds[index] = CreateRgb(red, green, blue);
}

Ws28xxDeviceModel::rgb Ws28xxDeviceModel::CreateRgb(uint8_t red, uint8_t green, uint8_t blue) const
{
    return { red, green, blue };
}
