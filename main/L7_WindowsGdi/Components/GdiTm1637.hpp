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
        uint16_t y);
    ~GdiTm1637();

    void SetDeviceModel(
        Tm1637DeviceModel& deviceModel);

    void Update(HDC* hdc);

private:
    Tm1637DeviceModel& GetDeviceModel();

    uint16_t D(
        uint16_t value) const;
    std::string GetStringRepresentation();

    bool _hasColon;
    uint16_t _x;
    uint16_t _y;
    HFONT _sevenDigitsFont;
    HBRUSH _backgroundBrush;

    Tm1637DeviceModel* _deviceModel;
};
