#include "GdiLcd2004.hpp"
#include "../../L5_DeviceModels/Lcd2004/Lcd2004DeviceModel.hpp"
#include "../../L9_Utilities/Log/Log.hpp"
#include "windows.h"

const int LENGTH = 100;
const int WIDTH = 40;

GdiLcd2004::GdiLcd2004(
    int x,
    int y, 
    Lcd2004DeviceModel& lcd2004DeviceModel)
:   _x(x), 
    _y(y), 
    _monoFont(nullptr),
    _lcd2004DeviceModel(lcd2004DeviceModel)
{
    _monoFont = CreateFont(20, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_DEFAULT_PRECIS,
        CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, FIXED_PITCH | FF_MODERN, L"Consolas");   // monospace font
    _backgroundBrush = CreateSolidBrush(RGB(0, 0, 0));
    _bezelBrush = CreateSolidBrush(RGB(0, 96, 0));

}

GdiLcd2004::~GdiLcd2004()
{
    DeleteObject(_backgroundBrush);
    DeleteObject(_bezelBrush);
}

int GdiLcd2004::D(
    int value)
{
    return value * 2;
}

/// @brief Updates the GDI representation of the LCD 2004 display based on the current state of the Lcd2004DeviceModel.
/// @details It is called typically 4 times per state change, because every loop, only one line is changed for reducing
/// the time it takes for a full loop (as the LCD update is quite expensive.
void GdiLcd2004::Update(
    HDC* hdc)
{
    if (!_lcd2004DeviceModel.IsDirty())
    {
        return;
    }

    // Draw the LCD 2004 display background
    	
    RECT rectMain { _x, _y, _x + D(LENGTH), _y + D(WIDTH) };
    FillRect(*hdc, &rectMain, _backgroundBrush);
    	
    RECT rectBezel{ _x + D(2), _y + D(3), _x + D(LENGTH - 2), _y + D(WIDTH - 3) };
    FillRect(*hdc, &rectBezel, _bezelBrush);
    
    // Text
    SetTextColor(*hdc, RGB(0, 255, 0));
    SetBkMode(*hdc, TRANSPARENT);
    HFONT oldFont = (HFONT)SelectObject(*hdc, _monoFont);
    
    for (int lineIndex = 0; lineIndex < 4; ++lineIndex)
    {
        const std::string_view lineContent = _lcd2004DeviceModel.GetLine(lineIndex);
        char tmp[21];
        memcpy(tmp, lineContent.data(), 20);
        tmp[20] = '\0';
        TextOutA(*hdc, _x , _y + D(4 + lineIndex * 7), tmp, 20);
    }

    SelectObject(*hdc, oldFont);
}
