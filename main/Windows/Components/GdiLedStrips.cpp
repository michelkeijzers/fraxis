#include "GdiLedStrips.hpp"
#include "../GdiScreen.hpp"

const int LENGTH = 500;
const int WIDTH = 15; // Per led strip

GdiLedStrips::GdiLedStrips(GdiScreen& gdiScreen, int x, int y)
	: _gdiScreen(gdiScreen), _x(x), _y(y)
{
	for (int i = 0; i < 360; ++i)
	{
		_leds[i] = { 0, 0, 0 }; // Initialize all LEDs to off (black)
	}
}

GdiLedStrips::~GdiLedStrips()
{}

void GdiLedStrips::SetLed(int index, uint8_t red, uint8_t green, uint8_t blue)
{
	if (index >= 0 && index < 360)
	{
		_leds[index].red = red;
		_leds[index].green = green;
		_leds[index].blue = blue;
	}
}

void GdiLedStrips::Update(HDC* hdc)
{
	// Draw the LED strips background
	HBRUSH brushMain = CreateSolidBrush(RGB(128, 128, 128));
	for (int ledStripIndex = 0; ledStripIndex < 5; ledStripIndex++)
	{
		RECT rectMain{ _x, _y + D(ledStripIndex * WIDTH), _x + D(LENGTH), _y + D((ledStripIndex + 1) * WIDTH) - 2 };
		FillRect(*hdc, &rectMain, brushMain);
	}

	for (int ledIndex = 0; ledIndex < 360; ledIndex++)
	{
		int ledStripIndex = ledIndex / 72;
		int ledPositionInStrip = ledIndex % 72;
		if (ledStripIndex % 2 == 1)
		{
			ledPositionInStrip = 72 - 1 - ledPositionInStrip; // Reverse the order for odd strips
		}
		LedStripRgb color = _leds[ledIndex];
		HBRUSH brushLed = CreateSolidBrush(RGB(color.red, color.green, color.blue));
		RECT rectLed{ _x + D(ledPositionInStrip * 7), _y + D(ledStripIndex * WIDTH), 
			_x + D((ledPositionInStrip + 1) * 7) - 2, _y + D((ledStripIndex + 1) * WIDTH) - 2 };
		FillRect(*hdc, &rectLed, brushLed);
		DeleteObject(brushLed);
	}

	DeleteObject(brushMain);
}
