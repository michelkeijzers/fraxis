#include "LedStripModel.hpp"
#include <cstring>   // memcpy, memset
#include <cstdlib>   // malloc, free

LedStripModel::LedStripModel(uint16_t numberOfLeds)
    : _numberOfLeds(numberOfLeds)
{
    _bufferA = static_cast<Pixel*>(std::malloc(sizeof(Pixel) * numberOfLeds));
    _bufferB = static_cast<Pixel*>(std::malloc(sizeof(Pixel) * numberOfLeds));

    // Initialize both buffers to black
    if (_bufferA != nullptr)
    {
        std::memset(_bufferA, 0, sizeof(Pixel) * numberOfLeds);
    }

    if (_bufferB != nullptr)
    {
        std::memset(_bufferB, 0, sizeof(Pixel) * numberOfLeds);
    }

    _activeBuffer = _bufferA;
}

LedStripModel::~LedStripModel()
{
    std::free(_bufferA);
    std::free(_bufferB);
}

void LedStripModel::SetPixel(uint16_t index, uint8_t red, uint8_t green, uint8_t blue)
{
    if (index >= _numberOfLeds)
    {
        return;
    }

    _activeBuffer[index].red   = red;
    _activeBuffer[index].green = green;
    _activeBuffer[index].blue  = blue;

    _dirtyFlag.MarkDirty();
}

void LedStripModel::Fill(uint8_t red, uint8_t green, uint8_t blue)
{
    for (uint16_t i = 0; i < _numberOfLeds; ++i)
    {
        _activeBuffer[i].red   = red;
        _activeBuffer[i].green = green;
        _activeBuffer[i].blue  = blue;
    }

    _dirtyFlag.MarkDirty();
}

LedStripModel::Pixel LedStripModel::GetPixel(uint16_t index) const
{
    if (index >= _numberOfLeds)
    {
        return Pixel{0,0,0};
    }

    return _activeBuffer[index];
}

LedStripModel::Pixel* LedStripModel::GetActiveBuffer()
{
    return _activeBuffer;
}

LedStripModel::Pixel* LedStripModel::GetInactiveBuffer()
{
    return (_activeBuffer == _bufferA) ? _bufferB : _bufferA;
}

uint32_t LedStripModel::ComputeInactiveBufferCurrent()
{
    static constexpr uint8_t MAX_CHANNEL_MILLI_AMPERES = 20;

    const Pixel* inactiveBuffer = GetInactiveBuffer();

    uint32_t totalCurrent = 0;
    for (uint16_t i = 0; i < _numberOfLeds; ++i)
    {
        totalCurrent += (inactiveBuffer[i].red * MAX_CHANNEL_MILLI_AMPERES) / 255;
        totalCurrent += (inactiveBuffer[i].green * MAX_CHANNEL_MILLI_AMPERES) / 255;
        totalCurrent += (inactiveBuffer[i].blue * MAX_CHANNEL_MILLI_AMPERES) / 255;
    }
    return totalCurrent;
}

void LedStripModel::ScaleInactiveBuffer(uint16_t scale)
{
    Pixel* inactiveBuffer = GetInactiveBuffer();
    if (scale >= 256)
    {
        return; // No limiting needed
    }

    for (uint16_t i = 0; i < _numberOfLeds; ++i)
    {
        inactiveBuffer[i].red   = (inactiveBuffer[i].red   * scale) >> 8;
        inactiveBuffer[i].green = (inactiveBuffer[i].green * scale) >> 8;
        inactiveBuffer[i].blue  = (inactiveBuffer[i].blue  * scale) >> 8;
    }
}

void LedStripModel::SwapBuffers()
{
    Pixel* inactiveBuffer = GetInactiveBuffer();
    std::memcpy(inactiveBuffer, _activeBuffer, sizeof(Pixel) * _numberOfLeds);
    _activeBuffer = inactiveBuffer;
    _dirtyFlag.ClearDirty();
}
