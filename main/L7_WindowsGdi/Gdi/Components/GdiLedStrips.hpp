#pragma once

#include <cstdint>
#include <windows.h>

class GdiScreen;

class GdiLedStrips
{
public:
	GdiLedStrips(GdiScreen& gdiScreen, int x, int y);

	void Update(HDC* hdc);

    GdiScreen& GetGdiScreen();

private:
    uint8_t ApplyGamma(uint8_t value);

	GdiScreen& _gdiScreen;

	int D(int value) { return value * 2; } // Placeholder for scaling function)

    int _x;
    int _y;
};

