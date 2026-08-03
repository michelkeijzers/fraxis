#pragma once

#include <cstdint>
#include <windows.h>

class Ws28xxDeviceModel;

class GdiLedStrips
{
public:
    GdiLedStrips(
        uint16_t numberOfLedStrips, 
        uint16_t ledsPerLedStrip, 
        uint16_t x, 
        uint16_t y, 
        Ws28xxDeviceModel& ws28xxDeviceModel);

    ~GdiLedStrips();

    void Update(
        HDC* hdc);

private:
    int D(int value);

    uint16_t _numberOfLedStrips;
    uint16_t _ledsPerLedStrip;
    uint16_t _x;
    uint16_t _y;

    HBRUSH _ledBackgroundBrush;

    Ws28xxDeviceModel& _ws28xxDeviceModel;
};
