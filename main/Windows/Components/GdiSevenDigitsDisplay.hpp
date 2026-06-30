#pragma once

#include <windows.h>

class GdiScreen;

class GdiSevenDigitsDisplay
{
public:
	GdiSevenDigitsDisplay(GdiScreen& gdiScreen, int nrOfDigits, bool hasColon, int x, int y);
	~GdiSevenDigitsDisplay();

	void Update(HDC* hdc);

private:
	GdiScreen& _gdiScreen;
	int _x;
	int _y;

	int D(int value) { return value * 2; } // Placeholder for scaling function)

	int _nrOfDigits;
	bool _hasColon;
	int _value;
	bool _colon;
	bool _dots[8];
};

