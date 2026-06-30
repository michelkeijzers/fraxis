#pragma once

#include <windows.h>

class GdiScreen;
class Lcd1602Display;

class GdiLcd1602Display
{
public:
	GdiLcd1602Display(GdiScreen& gdiScreen, Lcd1602Display& lcdDisplay, int x, int y);
	~GdiLcd1602Display();

	void Update(HDC* hdc);

private:
	GdiScreen& _gdiScreen;
	Lcd1602Display& _lcdDisplay;
	int _x;
	int _y;

	HFONT _monoFont;
	void CreateMonoFont();

	int D(int value) { return value * 2; } // Placeholder for scaling function)
};

