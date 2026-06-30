#pragma once

#include <stdint.h>
#include <windows.h>

class GdiScreen;

class  LedStripRgb
{
public:
	uint8_t red;
	uint8_t green;
	uint8_t blue;
};

class GdiLedStrips
{
public:
	GdiLedStrips(GdiScreen& gdiScreen, int x, int y);
	~GdiLedStrips();

	void Update(HDC* hdc);

	void SetLed(int index, uint8_t red, uint8_t green, uint8_t blue);

private:
	GdiScreen& _gdiScreen;
	int _x;
	int _y;

	int D(int value) { return value * 2; } // Placeholder for scaling function)

	LedStripRgb _leds[360];
};

