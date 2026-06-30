#include "GdiSevenDigitsDisplay.hpp"
#include "../GdiScreen.hpp"

const int LENGTH = 10; // Per digit
const int WIDTH = 20; 

GdiSevenDigitsDisplay::GdiSevenDigitsDisplay(GdiScreen& gdiScreen, int nrOfDigits, bool hasColon, int x, int y)
	: _gdiScreen(gdiScreen),
	_nrOfDigits(nrOfDigits),
	_hasColon(hasColon),
	_x(x), 
	_y(y), 
	_colon(true),
	_dots { true, true, true, true, true, true, true, true },
	_value(0)
{
}

GdiSevenDigitsDisplay::~GdiSevenDigitsDisplay()
{}


void GdiSevenDigitsDisplay::Update(HDC* hdc)
{
	HBRUSH hBrush = CreateSolidBrush(RGB(0, 0, 0));
	RECT rect{ _x, _y, _x + D(LENGTH * _nrOfDigits + 5), _y + D(WIDTH) };
	FillRect(*hdc, &rect, hBrush);
	DeleteObject(hBrush);

	HFONT hFont = CreateFont(
		40, 0, 0, 0, FW_BOLD, TRUE, FALSE, FALSE,
		ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
		DEFAULT_QUALITY, FIXED_PITCH | FF_MODERN,
		L"DS-DIGITAL"
	);

	SetTextColor(*hdc, RGB(255, 0, 0));
	HFONT old = (HFONT)SelectObject(*hdc, hFont);
	TextOut(*hdc, _x + 3, _y + 3, L"1234", 4);

	if (_hasColon && _colon)
	{
		TextOut(*hdc, _x + D(LENGTH * 2 - 4 ), _y + 1, L":", 1);
	}
	
	for (int dotIndex = 0; dotIndex < _nrOfDigits; ++dotIndex)
	{
		if (_dots[dotIndex])
		{
			TextOut(*hdc, _x + D((LENGTH + 0.8) * dotIndex + 5), _y + 2, L".", 1);
		}
	}

	DeleteObject(hFont);
}
