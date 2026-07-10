#pragma once

#include <cstdint>
#include <windows.h>

class GdiScreen;
class WindowsLedStripDriver;

class GdiLedStrips
{
public:
	GdiLedStrips(GdiScreen& gdiScreen, WindowsLedStripDriver& windowsLedStripDriver, int x, int y);
	~GdiLedStrips();

	void Update(HDC* hdc);

private:
    uint8_t ApplyGamma(uint8_t value);

	GdiScreen& _gdiScreen;

	int D(int value) { return value * 2; } // Placeholder for scaling function)

    WindowsLedStripDriver& _windowsLedStripDriver;

    int _x;
    int _y;
};

