
#include "GdiButton.hpp"
#include "../GdiScreen.hpp"
#include <string>
#include "../Components/WindowsMcp23017.hpp"
#include "../../Core/Components/PinIoMappings.hpp"

GdiButton::GdiButton(WindowsMcp23017& windowsMcp23017, PinIoMappings::EId id,
    GdiScreen& gdiScreen, int x, int y, int w, int h)
	: IGdiMouseInput(),
	_windowsMcp23017(windowsMcp23017),
    _id(id),
	_gdiScreen(gdiScreen)
{
	r = { x, y, x + w, y + h };
}

bool GdiButton::HitTest(int x, int y)
{
	return x >= r.left && x <= r.right &&
		   y >= r.top  && y <= r.bottom;
}

void GdiButton::OnMouseDown(int x, int y)
{
	if (HitTest(x, y))
	{
		pressed = true;
		hovered = true;
		_windowsMcp23017.SimulateSetGpioPin(_id, 1);
	}
}

void GdiButton::OnMouseMove(int x, int y)
{
	hovered = HitTest(x, y);

	// If mouse leaves the button while pressed, cancel press
    if (!hovered)
    {
        pressed = false;
    }
}

void GdiButton::OnMouseUp(int x, int y)
{
	bool wasPressed = pressed;
	pressed = false;

	if (wasPressed && HitTest(x, y))
	{
		_windowsMcp23017.SimulateSetGpioPin(_id, 0);
	}
}

void GdiButton::Update(HDC* hdc)
{
	// Colors
	COLORREF normalColor = RGB(150, 50, 50);
	COLORREF hoverColor = RGB(200, 50, 50);
	COLORREF pressedColor = RGB(255, 50, 50);
	COLORREF borderColor = RGB(40, 40, 40);
	COLORREF textColor = RGB(20, 20, 20);

	// Determine fill color
	COLORREF fillColor =
		pressed ? pressedColor :
		hovered ? hoverColor :
		normalColor;

	// Draw filled rectangle
	HBRUSH brush = CreateSolidBrush(fillColor);
	HPEN pen = CreatePen(PS_SOLID, 2, borderColor);

	HBRUSH oldBrush = (HBRUSH)SelectObject(*hdc, brush);
	HPEN oldPen = (HPEN)SelectObject(*hdc, pen);

	Rectangle(*hdc, r.left, r.top, r.right, r.bottom);

	SelectObject(*hdc, oldBrush);
	SelectObject(*hdc, oldPen);

	DeleteObject(brush);
	DeleteObject(pen);

	// Draw centered text (optional)
	std::string label = "S";
	if (!label.empty())
	{
		HFONT hFont = CreateFont(
			-40,                // height (negative = character height)
			0,                  // width (0 = auto)
			0, 0,               // angle
			FW_BOLD,            // weight (FW_BOLD for bold)
			FALSE,              // italic
			FALSE,              // underline
			FALSE,              // strikeout
			DEFAULT_CHARSET,
			OUT_DEFAULT_PRECIS,
			CLIP_DEFAULT_PRECIS,
			DEFAULT_QUALITY,
			DEFAULT_PITCH | FF_DONTCARE,
			L"Consolas");

		HFONT oldFont = (HFONT)SelectObject(*hdc, hFont);
		SetBkMode(*hdc, TRANSPARENT);
		SetTextColor(*hdc, textColor);

		DrawTextA(*hdc, label.c_str(), -1, &r,
			DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		SelectObject(*hdc, oldFont);
		DeleteObject(hFont);
	}
}
