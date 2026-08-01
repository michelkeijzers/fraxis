#pragma once

#include "windows.h"

class Lcd2004DeviceModel;

class GdiLcd2004
{
public:
    GdiLcd2004(int x, int y, Lcd2004DeviceModel& lcd2004DeviceModel);
    ~GdiLcd2004();

    void Update(HDC* hdc);

private:
    int D(int value);
    void CreateMonoFont();

    int _x;
    int _y;
    HFONT _monoFont;
    Lcd2004DeviceModel& _lcd2004DeviceModel;
};
