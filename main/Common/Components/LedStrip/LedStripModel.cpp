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

const LedStripModel::Pixel* LedStripModel::GetBuffer() const
{
    return _activeBuffer;
}

void LedStripModel::SwapBuffers()
{
    Pixel* inactive = (_activeBuffer == _bufferA) ? _bufferB : _bufferA;
    std::memcpy(inactive, _activeBuffer, sizeof(Pixel) * _numberOfLeds);
    _activeBuffer = inactive;
    _dirtyFlag.ClearDirty();
}
