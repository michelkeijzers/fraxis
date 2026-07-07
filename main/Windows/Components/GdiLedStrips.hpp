#pragma once

#include <stdint.h>
#include <windows.h>

class GdiScreen;
class WindowsLedStrips;

class GdiLedStrips
{
public:
	GdiLedStrips(GdiScreen& gdiScreen, WindowsLedStrips& ledStrips, int x, int y);
	~GdiLedStrips();

	void Update(HDC* hdc);

private:
	GdiScreen& _gdiScreen;

	int D(int value) { return value * 2; } // Placeholder for scaling function)

    WindowsLedStrips& _windowsLedStrips;

    int _x;
    int _y;
};

