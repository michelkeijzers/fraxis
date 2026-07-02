#pragma once

#include <windows.h>

class GdiScreen;
class WindowsTm1637;

class GdiSevenDigitsDisplay
{
public:
	GdiSevenDigitsDisplay(GdiScreen& gdiScreen, WindowsTm1637& tm1637, int nrOfDigits, bool hasColon, int x, int y);
	~GdiSevenDigitsDisplay();

	void Update(HDC* hdc);

private:
	GdiScreen& _gdiScreen;
	WindowsTm1637& _tm1637;
	int _x;
	int _y;

	int D(int value) { return value * 2; } // Placeholder for scaling function)

	int _nrOfDigits;
	bool _hasColon;
};
