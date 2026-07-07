#pragma once

#include <cstdint>
#include "IComponent.hpp"

class LedStrips : public IComponent
{
public:
    struct Pixel
    {
        uint8_t red;
        uint8_t green;
        uint8_t blue;
    };

    static constexpr uint8_t NumberOfLedStrips = 5;
    static constexpr uint16_t NumberOfLedsPerLedStrip = 72;
    static constexpr uint16_t NumberOfLeds = NumberOfLedStrips * NumberOfLedsPerLedStrip;

    enum EOrientation
    {
        Horizontal, // 5 Rows of 72 columns, from bottom to top, left to right
        Vertical    // 72 Rows of 5 columns, from bottom to top, left to right
    };

    LedStrips();
    virtual ~LedStrips() = default;

    void SetPixel(uint16_t index, uint8_t r, uint8_t g, uint8_t b);

    void Fill(uint8_t r, uint8_t g, uint8_t b);

    const Pixel* GetBuffer() const;
    Pixel GetPixel(uint16_t index);

    void SetOrientation(EOrientation orientation);

protected:
    Pixel _buffer[NumberOfLeds];
    EOrientation _orientation;
};
