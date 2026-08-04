#pragma once

#include <Windows.h>
#include <string>

class Tm1637DeviceModel;

class GdiTm1637
{
public:
    GdiTm1637(
        bool hasColon, 
        uint16_t x,
        uint16_t y,
        Tm1637DeviceModel& tm1637DeviceModel);
    ~GdiTm1637();

    void Update(HDC* hdc);

private:
    uint16_t D(
        uint16_t value) const;
    std::string GetStringRepresentation();

    bool _hasColon;
    uint16_t _x;
    uint16_t _y;
    HFONT _sevenDigitsFont;
    HBRUSH _backgroundBrush;

    Tm1637DeviceModel& _tm1637DeviceModel;
};
