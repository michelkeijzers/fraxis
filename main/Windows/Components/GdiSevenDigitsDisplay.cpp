#include "GdiSevenDigitsDisplay.hpp"
#include "../GdiScreen.hpp"
#include "../../Common/Components/Tm1637/Tm1637Model.hpp"

const int LENGTH = 10; // Per digit
const int WIDTH = 20; 

GdiSevenDigitsDisplay::GdiSevenDigitsDisplay(
    GdiScreen& gdiScreen, Tm1637Model& tm1637Model, bool hasColon, int x, int y)
	: _gdiScreen(gdiScreen),
	_tm1637Model(tm1637Model),
	_hasColon(hasColon),
	_x(x), 
	_y(y)
{
}

GdiSevenDigitsDisplay::~GdiSevenDigitsDisplay()
{}


void GdiSevenDigitsDisplay::Update(HDC* hdc)
{
	HBRUSH hBrush = CreateSolidBrush(RGB(0, 0, 0));
	RECT rect{ _x, _y, _x + D(LENGTH * (_tm1637Model.GetNumberOfDigits() + 1) + 5), _y + D(WIDTH)}; // +1 for auxiliary segment
	FillRect(*hdc, &rect, hBrush);
	DeleteObject(hBrush);

	HFONT hFont = CreateFont(
		28, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE,
		ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
		DEFAULT_QUALITY, FIXED_PITCH | FF_MODERN,
		L"DSEG7 CLASSIC"
	);

	SetTextColor(*hdc, RGB(255, 0, 0));
	HFONT old = (HFONT)SelectObject(*hdc, hFont);
	char output[32]; 
    _tm1637Model.GetStringRepresentation(output);

    SIZE sz;
    int outputLength = static_cast<int>(strlen(output));
    GetTextExtentPoint32A(*hdc, output, outputLength, &sz);
	TextOutA(*hdc, rect.right - sz.cx - 3, _y + 5, output, outputLength);

	DeleteObject(hFont);
}
