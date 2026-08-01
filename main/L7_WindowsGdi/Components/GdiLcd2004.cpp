#include "GdiLcd2004.hpp"
#include "../../L5_DeviceModels/Lcd2004/Lcd2004DeviceModel.hpp"
#include "../../L9_Utilities/Log/Log.hpp"
#include "windows.h"

const int LENGTH = 80;
const int WIDTH = 40;

GdiLcd2004::GdiLcd2004(int x, int y, Lcd2004DeviceModel& lcd2004DeviceModel)
    : _x(x), _y(y), _monoFont(nullptr), _lcd2004DeviceModel(lcd2004DeviceModel)
{
}

GdiLcd2004::~GdiLcd2004()
{
}

int GdiLcd2004::D(int value)
{
    return value * 2;
}

void GdiLcd2004::CreateMonoFont()
{
	_monoFont = CreateFont(
		20, 0, 0, 0,
		FW_BOLD,
		FALSE, FALSE, FALSE,
		ANSI_CHARSET,
		OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS,
		DEFAULT_QUALITY,
		FIXED_PITCH | FF_MODERN,
		L"Consolas"   // monospace font
	);
}

void GdiLcd2004::Update(HDC* hdc)
{
    // Draw the LCD 2004 display background
    HBRUSH brush = CreateSolidBrush(RGB(0, 0, 0));
    	
    HBRUSH brushMain = CreateSolidBrush(RGB(0, 0, 0));
    RECT rectMain { _x, _y, _x + D(LENGTH), _y + D(WIDTH) };
    FillRect(*hdc, &rectMain, brushMain);
    DeleteObject(brushMain);
    	
    HBRUSH brushBezel = CreateSolidBrush(RGB(0, 96, 0));
    RECT rectBezel{ _x + D(2), _y + D(3), _x + D(LENGTH - 2), _y + D(WIDTH - 3) };
    FillRect(*hdc, &rectBezel, brushBezel);
    DeleteObject(brushBezel);
    
    // Text
    SetTextColor(*hdc, RGB(0, 255, 0));
    SetBkMode(*hdc, TRANSPARENT);
    HFONT oldFont = (HFONT)SelectObject(*hdc, _monoFont);
    
    Log::Text("xxx L7 GdiLcd2004::Update");
    for (int lineIndex = 0; lineIndex < 4; ++lineIndex)
    {
        const std::string_view lineContent = _lcd2004DeviceModel.GetLine(lineIndex);
        Log::Text("xxx L7 GdiLcd2004::Update line " + std::to_string(lineIndex) + ": " + std::string(lineContent));
        char tmp[21];
        memcpy(tmp, lineContent.data(), 20);
        tmp[20] = '\0';
        TextOutA(*hdc, _x + D(5), _y + D(1 + lineIndex * 7), tmp, 20);
    }

    SelectObject(*hdc, oldFont);
    DeleteObject(brush);
}
