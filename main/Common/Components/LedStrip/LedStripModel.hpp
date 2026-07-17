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

    void CopyAppsBufferToDriverBuffer();
    uint32_t ComputeDriverBufferCurrent();
    void ScaleDriverBuffer(uint16_t scale);
    
    Pixel* GetDriverBuffer() { return _driverBuffer; }

private:
    Pixel* _appsBuffer;
    Pixel* _driverBuffer;

    uint16_t _numberOfLeds;
};
