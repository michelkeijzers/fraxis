#include "GdiLedStrips.hpp"
#include "../GdiScreen.hpp"
#include "WindowsLedStripDriver.hpp"

#include <algorithm>

const int LENGTH = 500;
const int WIDTH = 15; // Per led strip

GdiLedStrips::GdiLedStrips(GdiScreen& gdiScreen, WindowsLedStripDriver& windowsLedStripDriver, int x, int y)
	: _gdiScreen(gdiScreen), _windowsLedStripDriver(windowsLedStripDriver), _x(x), _y(y)
{
}

GdiLedStrips::~GdiLedStrips()
{}


void GdiLedStrips::Update(HDC* hdc)
{
	// Draw the LED strips background
	HBRUSH brushMain = CreateSolidBrush(RGB(64, 64, 64));
	for (int ledStripIndex = 0; ledStripIndex < 5; ledStripIndex++)
	{
		RECT rectMain{ _x - 5, _y + D(ledStripIndex * WIDTH), _x + D(LENGTH + 10), _y + D((ledStripIndex + 1) * WIDTH) };
		FillRect(*hdc, &rectMain, brushMain);
	}

    std::vector<LedStripModel::Pixel> buffer = _windowsLedStripDriver.GetBuffer();
	for (int ledIndex = 0; ledIndex < buffer.size(); ledIndex++)
	{
		int ledStripIndex = ledIndex / 72;
		int ledPositionInStrip = ledIndex % 72;
		if (ledStripIndex % 2 == 1)
		{
			ledPositionInStrip = 72 - 1 - ledPositionInStrip; // Reverse the order for odd strips
		}
        LedStripModel::Pixel pixel = buffer[ledIndex];
		HBRUSH brushLed = CreateSolidBrush(RGB(pixel.red, pixel.green, pixel.blue));
		//RECT rectLed{ _x + D(ledPositionInStrip * 7), _y + D(ledStripIndex * WIDTH), 
		//	_x + D((ledPositionInStrip + 1) * 7) - 2, _y + D((ledStripIndex + 1) * WIDTH) - 2 };


		//FillRect(*hdc, &rectLed, brushLed);

        HBRUSH brushLedForCircle = CreateSolidBrush(RGB(pixel.red, pixel.green, pixel.blue));
        HBRUSH oldBrush = (HBRUSH)SelectObject(*hdc, brushLedForCircle);

        // compute rect boundaries
        int left = _x + D(ledPositionInStrip * 7);
        int top = _y + D(ledStripIndex * WIDTH);
        int right = _x + D((ledPositionInStrip + 1) * 7) - 2;
        int bottom = _y + D((ledStripIndex + 1) * WIDTH) - 2;

        // convert rect → circle
        int cx = (left + right) / 2;
        int cy = (top + bottom) / 2;
        int radius = ((right - left) < (bottom - top)
            ? (right - left)
            : (bottom - top)) / 2;
        radius += 1;

        // draw circle
        Ellipse(*hdc, cx - radius, cy - radius, cx + radius, cy + radius);

        // cleanup
        SelectObject(*hdc, oldBrush);
        DeleteObject(brushLedForCircle);

		DeleteObject(brushLed);
	}

	DeleteObject(brushMain);
}
