
#include "GdiLed.hpp"
#include "../GdiScreen.hpp"
#include <string>
#include "../../Core/Components/PinIo.hpp"
#include "../Components/WindowsMcp23017.hpp"
#include "../../Core/Components/PinIoMappings.hpp"
#include "../../Core/SharedUtils/Debug.hpp"

GdiLed::GdiLed(PinIo& pinIo, WindowsMcp23017& windowsMcp23017, PinIoMappings::EIdBit idBit,
    GdiScreen& gdiScreen, int x, int y, int w, int h, std::string text, COLORREF rgbColorOff, COLORREF rgbColorOn)
	: _pinIo(pinIo), _windowsMcp23017(windowsMcp23017),
    _idBit(idBit),
	_gdiScreen(gdiScreen), 
    _text(text), _rgbColorOff(rgbColorOff), _rgbColorOn(rgbColorOn)
{
	_r = { x, y, x + w, y + h };
}

void GdiLed::Update(HDC* hdc)
{
    // Sizes (tweak to taste)
    const int bezelRadius = 12;   // outer ring
    const int ledRadius = 9;   // inner LED

    // Outer bezel (dark ring)
    HBRUSH bezelBrush = CreateSolidBrush(RGB(80, 80, 80));
    HBRUSH oldBrush = (HBRUSH)SelectObject(*hdc, bezelBrush);
    HPEN   bezelPen = CreatePen(PS_SOLID, 1, RGB(20, 20, 20));
    HPEN   oldPen = (HPEN)SelectObject(*hdc, bezelPen);

    Ellipse(*hdc,
        _r.left - bezelRadius, _r.top - bezelRadius,
        _r.left + bezelRadius, _r.top + bezelRadius);

    // LED lens

    bool on = _pinIo.GetGpioStates() & (1 << (uint8_t)_idBit);
    if (_idBit == PinIoMappings::EIdBit::PauseLed)
        Debug::PrintInt("\nGDI PauseLed: ", on ? 1 : 0);


    
    HBRUSH ledBrush = CreateSolidBrush(on ? _rgbColorOn : _rgbColorOff);
    SelectObject(*hdc, ledBrush);

    Ellipse(*hdc,
        _r.left - ledRadius, _r.top - ledRadius,
        _r.left + ledRadius, _r.top + ledRadius);


    // Cleanup
    SelectObject(*hdc, oldBrush);
    SelectObject(*hdc, oldPen);
    DeleteObject(bezelBrush);
    DeleteObject(bezelPen);
    DeleteObject(ledBrush);

    HFONT hFont = CreateFontA(
        24, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE,
        ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
        DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE,
        "DSEG7 Classic Mono"   // or any font you want
    );

    HFONT oldFont = (HFONT)SelectObject(*hdc, hFont);

    SetTextColor(*hdc, RGB(200, 200, 200));
    TextOutA(*hdc, _r.left + 15, _r.top - 12, _text.c_str(), (int) _text.size());

    SelectObject(*hdc, oldFont);
    DeleteObject(hFont);
}
