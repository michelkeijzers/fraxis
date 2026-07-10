#pragma once

#include <cstdint>
#include "../ComponentModel.hpp"

class LedStripModel : public ComponentModel
{
public:
    struct Pixel
    {
        uint8_t red;
        uint8_t green;
        uint8_t blue;
    };

    LedStripModel(uint16_t numberOfLeds);
    ~LedStripModel();

    void SetPixel(uint16_t index, uint8_t red, uint8_t green, uint8_t blue);
    void Fill(uint8_t red, uint8_t green, uint8_t blue);

    Pixel GetPixel(uint16_t index) const;

    Pixel* GetActiveBuffer() { return _activeBuffer; };
    Pixel* GetInactiveBuffer();
    uint32_t ComputeInactiveBufferCurrent();
    void ScaleInactiveBuffer(uint16_t scale);
    void SwapBuffers();

private:
    Pixel* _bufferA;
    Pixel* _bufferB;
    Pixel* _activeBuffer;

    uint16_t _numberOfLeds;
};
