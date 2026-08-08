#include "GdiLcd2004.hpp"
#include "../../L5_DeviceModels/Lcd2004/Lcd2004DeviceModel.hpp"
#include "../../L9_Utilities/Log/Log.hpp"
#include <Windows.h>

const int LENGTH = 100;
const int WIDTH = 40;

GdiLcd2004::GdiLcd2004(
    uint16_t x,
    uint16_t y)
:   _x(x), 
    _y(y), 
    _monoFont(nullptr)
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

Lcd2004DeviceModel& GdiLcd2004::GetDeviceModel()
{
    return *_deviceModel;
}

void GdiLcd2004::SetDeviceModel(
    Lcd2004DeviceModel& deviceModel)
{
    _deviceModel = &deviceModel;
}
uint16_t GdiLcd2004::D(
    uint16_t value) const
{
    return value * 2;
}

/// @brief Updates the GDI representation of the LCD 2004 display based on the current state of the Lcd2004DeviceModel.
/// @details It is called typically 4 times per state change, because every loop, only one line is changed for reducing
/// the time it takes for a full loop (as the LCD update is quite expensive.
void GdiLcd2004::Update(
    HDC* hdc)
{
    RECT rectMain { _x, _y, _x + D(LENGTH), _y + D(WIDTH) };
    FillRect(*hdc, &rectMain, _backgroundBrush);
    	
    RECT rectBezel{ _x + D(2), _y + D(3), _x + D(LENGTH - 2), _y + D(WIDTH - 3) };
    FillRect(*hdc, &rectBezel, _bezelBrush);
    
    // Text
    SetTextColor(*hdc, RGB(0, 255, 0));
    SetBkMode(*hdc, TRANSPARENT);
    auto oldFont = (HFONT)SelectObject(*hdc, _monoFont);
    
    for (uint8_t lineIndex = 0; lineIndex < 4; ++lineIndex)
    {
        const std::string_view lineContent = GetDeviceModel().GetLine(lineIndex);
        std::string line{ lineContent.begin(), lineContent.begin() + 20 };
        TextOutA(
            *hdc,
            _x + D(3),
            _y + D(4 + lineIndex * 7),
            line.c_str(),
            static_cast<int>(line.size())
        );
    }

    SelectObject(*hdc, oldFont);
}
