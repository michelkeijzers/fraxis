#pragma once
#include <string>
#include <windows.h>
#include "Components/GdiLedStrips.hpp"
#include "Components/GdiLcd1602Display.hpp"
#include "Components/GdiSevenDigitsDisplay.hpp"
#include "Components/GdiLed.hpp"
#include "IGdiMouseInput.hpp"
#include <vector>
#include <memory>

class PinIo;

class MenuSimulator;
class WindowsMcp23017;
class WindowsLcd1602Display;
class WindowsTm1637;

class GdiScreen
{
public:
	GdiScreen(PinIo& pinIo, WindowsMcp23017& windowsMcp23017, WindowsLcd1602Display& lcdDisplay, 
		WindowsTm1637& tm1637CentralPanel, WindowsTm1637& tm1637Player1, WindowsTm1637& tm1637Player2, 
		MenuSimulator& menuSimulator);

	void CreateMemoryDc(HWND hwnd, int width, int height);

	void Update();
	HDC GetMemDC() { return _memDC; }

	int D(int value) { return value * 2; } // Placeholder for scaling function)

	GdiLedStrips& GetLedStrips() { return _gdiLedStrips; }

	void OnMouseDown(int x, int y);
	void OnMouseMove(int x, int y);
	void OnMouseUp(int x, int y);
	
private:
	HDC _memDC;	
	HBITMAP _memBitmap;
	PinIo& _pinIo;
	WindowsMcp23017& _windowsMcp23017;
	WindowsLcd1602Display& _lcdDisplay;

	GdiLedStrips _gdiLedStrips;
	GdiLcd1602Display _gdiLcd1602Display;
	GdiSevenDigitsDisplay _gdiSevenDigitsDisplayCentralPanel;
	GdiSevenDigitsDisplay _gdiSevenDigitsDisplayPlayer1;
	GdiSevenDigitsDisplay _gdiSevenDigitsDisplayPlayer2;

    GdiLed _gdiPauseLed;
    GdiLed _gdiSelectLed;
    GdiLed _gdiSetupLed;
    GdiLed _gdiPlayer1Led;
    GdiLed _gdiPlayer2Led;

	std::vector<std::unique_ptr<IGdiMouseInput>> _gdiMouseInputs;
	MenuSimulator& _menuSimulator;

    HWND _hwnd;

public: 
    HWND GetHwnd() const { return _hwnd; }
};