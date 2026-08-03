#pragma once

#include <windows.h>
#include <string>

class Tm1637DeviceModel;

class GdiTm1637
{
public:
    GdiTm1637(
        bool hasColon, 
        int x, 
        int y,
        Tm1637DeviceModel& tm1637DeviceModel);
    ~GdiTm1637();

    void Update(HDC* hdc);

private:
    int D(
        int value);
    std::string GetStringRepresentation();

    bool _hasColon;
    int _x;
    int _y;
    HFONT _sevenDigitsFont;
    HBRUSH _backgroundBrush;

    Tm1637DeviceModel& _tm1637DeviceModel;
};
