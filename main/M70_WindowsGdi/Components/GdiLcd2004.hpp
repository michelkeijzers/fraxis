#pragma once

#include <cstdint>
#include <Windows.h>

class Lcd2004DeviceModel;

class GdiLcd2004
{
public:
    GdiLcd2004(
        uint16_t x,
        uint16_t y);
    ~GdiLcd2004();

    Lcd2004DeviceModel& GetDeviceModel();
    void SetDeviceModel(
        Lcd2004DeviceModel& deviceModel);

    void Update(
        HDC* hdc);

private:
    uint16_t D(
        uint16_t value) const;
    void CreateMonoFont();

    uint16_t _x;
    uint16_t _y;

    HFONT _monoFont;
    HBRUSH _backgroundBrush;
    HBRUSH _bezelBrush;

    Lcd2004DeviceModel* _deviceModel;
};
