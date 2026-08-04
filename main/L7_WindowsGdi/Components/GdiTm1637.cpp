#include "GdiTm1637.hpp"
#include "../../L5_DeviceModels/Tm1637/Tm1637DeviceModel.hpp"
#include "../../L9_Utilities/Log/Log.hpp"
#include "Windows.h"

const int LENGTH = 10; // Per digit
const int WIDTH = 20; 

GdiTm1637::GdiTm1637(
    bool hasColon,
    uint16_t x,
    uint16_t y,
    Tm1637DeviceModel& tm1637DeviceModel)
:   _hasColon(hasColon),
    _x(x),
    _y(y),
    _tm1637DeviceModel(tm1637DeviceModel)
{
    _sevenDigitsFont = CreateFont(28, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_DEFAULT_PRECIS,
        CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, FIXED_PITCH | FF_MODERN, L"DSEG7 CLASSIC");
    _backgroundBrush = CreateSolidBrush(RGB(0, 0, 0));
}

GdiTm1637::~GdiTm1637()
{
    DeleteObject(_backgroundBrush);
    DeleteObject(_sevenDigitsFont);
}

uint16_t GdiTm1637::D(
    uint16_t value) const
{
    return value * 2;
}

/// @brief Update Tm1637.
/// @details Do NOT check for model dirtyness, as the dirty flag gets reset before reaching this update.
/// @param hdc 
void GdiTm1637::Update(HDC* hdc)
{
    RECT rect{
        _x,
        _y,
        _x + D(LENGTH * (_tm1637DeviceModel.GetNrOfDigits() + 1) + 5),
        _y + D(WIDTH)
    };

    FillRect(*hdc, &rect, _backgroundBrush);

    SetTextColor(*hdc, RGB(255, 0, 0));
    auto oldFont = (HFONT)SelectObject(*hdc, _sevenDigitsFont);
    std::string outputStr = GetStringRepresentation();
    auto outputLength = static_cast<int>(outputStr.size());
    SIZE sz{};
    GetTextExtentPoint32A(*hdc, outputStr.c_str(), outputLength, &sz);
    TextOutA(
        *hdc,
        rect.right - sz.cx,
        _y + 5,
        outputStr.c_str(),
        outputLength
    );
    SelectObject(*hdc, oldFont);
}


std::string GdiTm1637::GetStringRepresentation()
{
    std::string output = "";
    for (uint8_t index = 0; index < _tm1637DeviceModel.GetNrOfDigits(); index++)
    {
        char character = _tm1637DeviceModel.GetCharacter(index);
        bool auxiliarySegment = _tm1637DeviceModel.GetAuxiliarySegment(index);
        std::string auxiliaryCharacter = "";
        if (auxiliarySegment)
        {
            auxiliaryCharacter = _hasColon ? ":" : ".";
        }
        output = character + auxiliaryCharacter + output;
    }
    return output;
}
