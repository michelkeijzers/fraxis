#pragma once

#include <windows.h>
#include <string>

#include "../../Core/Components/PinIoMappings.hpp"
#include <cstdint>

class PinIo;
class WindowsMcp23017;
class GdiScreen;

class GdiLed
{
private:
	RECT _r;

    PinIo& _pinIo;
	WindowsMcp23017& _windowsMcp23017;
	GdiScreen& _gdiScreen;

    PinIoMappings::EIdBit _idBit;

    std::string _text;
    COLORREF _rgbColorOff;
    COLORREF _rgbColorOn;

public:
	GdiLed(PinIo& pinIo, WindowsMcp23017& windowsMcp23017, PinIoMappings::EIdBit idBit,
        GdiScreen& gdiScreen, int x, int y, int w, int h, std::string text, COLORREF rgbColorOff, COLORREF rgbColorOn);
	
	void Update(HDC* hdc);
};
