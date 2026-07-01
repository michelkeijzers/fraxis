#pragma once
#include <string>
#include <windows.h>
#include "Components/GdiLcd1602Display.hpp"
#include "Components/GdiLedStrips.hpp"
#include "Components/GdiSevenDigitsDisplay.hpp"
#include "Components/GdiAtariJoystick.hpp"
#include "IGdiMouseInput.hpp"
#include <vector>
#include <memory>

class PinIo;
class MenuSimulator;
class WindowsMcp23017;

class GdiScreen
{
public:
	GdiScreen(PinIo& pinIo, WindowsMcp23017& windowsMcp23017, Lcd1602Display& lcdDisplay, MenuSimulator& menuSimulator);
	~GdiScreen();

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
	Lcd1602Display& _lcdDisplay;

	GdiLedStrips _gdiLedStrips;
	GdiLcd1602Display _gdiLcd1602Display;
	GdiSevenDigitsDisplay _gdiSevenDigitsDisplayCentralPanel;
	GdiSevenDigitsDisplay _gdiSevenDigitsDisplayPlayer1;
	GdiSevenDigitsDisplay _gdiSevenDigitsDisplayPlayer2;

	std::vector<std::unique_ptr<IGdiMouseInput>> _gdiMouseInputs;
	MenuSimulator& _menuSimulator;
};