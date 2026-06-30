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

class MenuSimulator;

class GdiScreen
{
public:
	GdiScreen(Lcd1602Display& lcdDisplay, MenuSimulator& menuSimulator);
	~GdiScreen();

	void CreateMemoryDc(HWND hwnd, int width, int height);

	void Update();
	HDC GetMemDC() { return _memDC; }

	int D(int value) { return value * 2; } // Placeholder for scaling function)

	GdiLedStrips& GetLedStrips() { return _gdiLedStrips; }

	void OnMouseDown(int x, int y);
	void OnMouseMove(int x, int y);
	void OnMouseUp(int x, int y);
		
	void OnJoystickChanged(GdiAtariJoystick::EId joystickId, uint8_t pressedItems);
	void OnSystemButtonChanged(bool pressed);

private:
	HDC _memDC;	
	HBITMAP _memBitmap;
	Lcd1602Display& _lcdDisplay;

	GdiLedStrips _gdiLedStrips;
	GdiLcd1602Display _gdiLcd1602Display;
	GdiSevenDigitsDisplay _gdiSevenDigitsDisplayCentralPanel;
	GdiSevenDigitsDisplay _gdiSevenDigitsDisplayPlayer1;
	GdiSevenDigitsDisplay _gdiSevenDigitsDisplayPlayer2;

	std::vector<std::unique_ptr<IGdiMouseInput>> _gdiMouseInputs;
	MenuSimulator& _menuSimulator;
};