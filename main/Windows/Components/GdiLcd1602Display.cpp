#include "GdiLcd1602Display.hpp"
#include "../GdiScreen.hpp"
#include "../../Core/Components/Lcd1602Display.hpp"

const int LENGTH = 80;
const int WIDTH = 20;

GdiLcd1602Display::GdiLcd1602Display(GdiScreen& gdiScreen, Lcd1602Display& lcdDisplay, int x, int y)
	: _gdiScreen(gdiScreen), _lcdDisplay(lcdDisplay), _x(x), _y(y)
{
	CreateMonoFont();
}

GdiLcd1602Display::~GdiLcd1602Display()
{
}

void GdiLcd1602Display::CreateMonoFont()
{
	_monoFont = CreateFont(
		20, 0, 0, 0,
		FW_BOLD,
		FALSE, FALSE, FALSE,
		ANSI_CHARSET,
		OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS,
		DEFAULT_QUALITY,
		FIXED_PITCH | FF_MODERN,
		L"Consolas"   // monospace font
	);
}

void GdiLcd1602Display::Update(HDC* hdc)
{
	// Draw the LCD 1602 display background
	HBRUSH brush = CreateSolidBrush(RGB(0, 0, 0));
	
	HBRUSH brushMain = CreateSolidBrush(RGB(0, 0, 0));
	RECT rectMain { _x, _y, _x + D(LENGTH), _y + D(WIDTH) };
	FillRect(*hdc, &rectMain, brushMain);
	DeleteObject(brushMain);
	
	HBRUSH brushBezel = CreateSolidBrush(RGB(0, 96, 0));
	RECT rectBezel{ _x + D(2), _y + D(3), _x + D(LENGTH - 2), _y + D(WIDTH - 3) };
	FillRect(*hdc, &rectBezel, brushBezel);
	DeleteObject(brushBezel);

	// Text
	SetTextColor(*hdc, RGB(0, 255, 0));
	SetBkMode(*hdc, TRANSPARENT);

	HFONT oldFont = (HFONT)SelectObject(*hdc, _monoFont);

	char tmp1[17];
	memcpy(tmp1, _lcdDisplay.GetLine1(), 16);
	tmp1[16] = '\0';

	char tmp2[17];
	memcpy(tmp2, _lcdDisplay.GetLine2(), 16);
	tmp2[16] = '\0';

	TextOutA(*hdc, _x + D(5), _y + D(1), tmp1, 16);
	TextOutA(*hdc, _x + D(5), _y + D(8), tmp2, 16);
	SelectObject(*hdc, oldFont);
	DeleteObject(brush);
}
