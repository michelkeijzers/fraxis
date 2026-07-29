#include "Ws28xxDeviceModel.hpp"
#include <cstring>   // memcpy, memset
#include <cstdlib>   // malloc, free

Ws28xxDeviceModel::Ws28xxDeviceModel(uint16_t numberOfLeds)
    : _numberOfLeds(numberOfLeds)
{
    _appsBuffer   = static_cast<Pixel*>(std::malloc(sizeof(Pixel) * numberOfLeds));
    _driverBuffer = static_cast<Pixel*>(std::malloc(sizeof(Pixel) * numberOfLeds));

    // Initialize both buffers to black
    if (_appsBuffer != nullptr)
    {
        std::memset(_appsBuffer, 0, sizeof(Pixel) * numberOfLeds);
    }

    if (_driverBuffer != nullptr)
    {
        std::memset(_driverBuffer, 0, sizeof(Pixel) * numberOfLeds);
    }
}

Ws28xxDeviceModel::~Ws28xxDeviceModel()
{
    std::free(_appsBuffer);
    std::free(_driverBuffer);
}

void Ws28xxDeviceModel::SetPixel(uint16_t index, uint8_t red, uint8_t green, uint8_t blue)
{
    if (index >= _numberOfLeds)
    {
        return;
    }

    _appsBuffer[index].red   = red;
    _appsBuffer[index].green = green;
    _appsBuffer[index].blue  = blue;

    MarkDirty();
}

void Ws28xxDeviceModel::Fill(uint8_t red, uint8_t green, uint8_t blue)
{
    for (uint16_t i = 0; i < _numberOfLeds; ++i)
    {
        _appsBuffer[i].red   = red;
        _appsBuffer[i].green = green;
        _appsBuffer[i].blue  = blue;
    }

    MarkDirty();
}

Ws28xxDeviceModel::Pixel Ws28xxDeviceModel::GetPixel(uint16_t index) const
{
    if (index >= _numberOfLeds)
    {
        return Pixel{0,0,0};
    }

    return _appsBuffer[index];
}

void Ws28xxDeviceModel::CopyAppsBufferToDriverBuffer()
{
    memcpy(_driverBuffer, _appsBuffer, sizeof(Ws28xxDeviceModel::Pixel) * _numberOfLeds);
}

uint32_t Ws28xxDeviceModel::ComputeDriverBufferCurrent()
{
    static constexpr uint8_t MAX_CHANNEL_MILLI_AMPERES = 20;

    uint32_t totalCurrent = 0;
    for (uint16_t i = 0; i < _numberOfLeds; ++i)
    {
        totalCurrent += (_driverBuffer[i].red * MAX_CHANNEL_MILLI_AMPERES) / 255;
        totalCurrent += (_driverBuffer[i].green * MAX_CHANNEL_MILLI_AMPERES) / 255;
        totalCurrent += (_driverBuffer[i].blue * MAX_CHANNEL_MILLI_AMPERES) / 255;
    }
    return totalCurrent;
}

void Ws28xxDeviceModel::ScaleDriverBuffer(uint16_t scale)
{
    if (scale >= 256)
    {
        return; // No limiting needed
    }

    for (uint16_t i = 0; i < _numberOfLeds; ++i)
    {
        _driverBuffer[i].red   = (_driverBuffer[i].red   * scale) >> 8;
        _driverBuffer[i].green = (_driverBuffer[i].green * scale) >> 8;
        _driverBuffer[i].blue  = (_driverBuffer[i].blue  * scale) >> 8;
    }
}
