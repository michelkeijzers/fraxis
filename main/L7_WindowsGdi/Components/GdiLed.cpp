#include "GdiLed.hpp"
#include "../../L5_DeviceModels/Mcp23017/Mcp23017DeviceModel.hpp"
#include "../../L9_Utilities/Log/Log.hpp"
#include "../../L9_Utilities/Assert/Assert.hpp"
#include "Windows.h"

const int LENGTH = 10; // Per digit
const int WIDTH = 20;

GdiLed::GdiLed(
    std::string_view text,
    EColor color,
    uint8_t bitNumber,
    uint16_t x,
    uint16_t y)
:   
    _text(text),
    _color(color),
    _bitNumber(bitNumber),
    _x(x),
    _y(y)
{
    _font = CreateFontA(
        24, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE,
        ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
        DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE,
        "DSEG7 Classic Mono"   // or any font you want
    );
    _bezelBrush = CreateSolidBrush(RGB(80, 80, 80));
    _bezelPen = CreatePen(PS_SOLID, 1, RGB(20, 20, 20));
    _offBrush = CreateSolidBrush(RGB(0, 0, 0));
    _redBrush = CreateSolidBrush(RGB(255, 0, 0));
    _greenBrush = CreateSolidBrush(RGB(0, 255, 0));
}

GdiLed::~GdiLed()
{
    DeleteObject(_font);
    DeleteObject(_bezelBrush);
    DeleteObject(_bezelPen);
    DeleteObject(_offBrush);
    DeleteObject(_redBrush);
    DeleteObject(_greenBrush);
}

Mcp23017DeviceModel& GdiLed::GetDeviceModel()
{
    return *_deviceModel;
}

void GdiLed::SetDeviceModel(
    Mcp23017DeviceModel& deviceModel)
{
    _deviceModel = &deviceModel;
}

uint16_t GdiLed::D(
    uint16_t value) const
{
    return value * 2;
}

/// @brief Update Tm1637.
/// @details Do NOT check for model dirtyness, as the dirty flag gets reset before reaching this update.
/// @param hdc 
void GdiLed::Update(
    HDC* hdc)
{
    // Sizes (tweak to taste)
    const int bezelRadius = 12;   // outer ring
    const int ledRadius = 9;   // inner LED

    // Outer bezel (dark ring)
    auto oldBrush = (HBRUSH)SelectObject(*hdc, _bezelBrush);
    auto   oldPen = (HPEN)SelectObject(*hdc, _bezelPen);

    Ellipse(*hdc,
        _x - bezelRadius, _y - bezelRadius,
        _x + bezelRadius, _y + bezelRadius);

    // LED lens
    bool on = GetDeviceModel().GetGpioStates() & (1 << (uint8_t)_bitNumber);
    HBRUSH ledBrush = GetBrush(on);
    SelectObject(*hdc, ledBrush);

    Ellipse(*hdc,
        _x - ledRadius, _y - ledRadius,
        _x + ledRadius, _y + ledRadius);

    // Cleanup
    SelectObject(*hdc, oldBrush);
    SelectObject(*hdc, oldPen);

    auto oldFont = (HFONT)SelectObject(*hdc, _font);
    SetTextColor(*hdc, RGB(200, 200, 200));
    TextOutA(*hdc, _x + 15, _y - 12, _text.c_str(), (int) _text.size());

    SelectObject(*hdc, oldFont);
}

HBRUSH GdiLed::GetBrush(
    bool on)
{
    if (on)
    {
        switch (_color)
        {
        case EColor::Red: return _redBrush; break;
        case EColor::Green: return _greenBrush; break;
        default: 
            Assert::Fail("Illegal color");
            break;
        }
    }
    return _offBrush;
}
