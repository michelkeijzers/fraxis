#pragma once

#include <windows.h>

class GdiScreen;
class WindowsTm1637;
class Tm1637Model;

class GdiSevenDigitsDisplay
{
public:
	GdiSevenDigitsDisplay(GdiScreen& gdiScreen, Tm1637Model& tm1637Model, bool hasColon, int x, int y);
	~GdiSevenDigitsDisplay();

	void Update(HDC* hdc);

private:
	GdiScreen& _gdiScreen;
	Tm1637Model& _tm1637Model;
	int _x;
	int _y;

	int D(int value) { return value * 2; } // Placeholder for scaling function)

	bool _hasColon;
};
