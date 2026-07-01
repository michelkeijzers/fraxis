#include "GdiAtariJoystick.hpp"
#include "../Components/WindowsMcp23017.hpp"
#include "../GdiScreen.hpp"
#include "../../Core/Components/PinIoMappings.hpp"


const int LENGTH = 90; // Entire joystick
const int WIDTH = 90; 

GdiAtariJoystick::GdiAtariJoystick(EId joystickId, PinIo& pinIo, WindowsMcp23017& windowsMcp23017, 
	GdiScreen& gdiScreen, int x, int y)
	: _joystickId(joystickId), _pinIo(pinIo), _windowsMcp23017(windowsMcp23017), 
	  _gdiScreen(gdiScreen), _x(x), _y(y)
{
}

GdiAtariJoystick::~GdiAtariJoystick()
{
}

bool GdiAtariJoystick::HitTest(int x, int y) 
{
	RECT r;
	r.left = _x;
	r.top = _y;
	r.right = _x + D(WIDTH);
	r.bottom = _y + D(LENGTH);

	return PtInRect(&r, POINT{ x, y });
}

void GdiAtariJoystick::OnMouseDown(int x, int y) 
{
	uint8_t newMask = 0;

	// Center of joystick
	int cx = _x + D(WIDTH / 2);
	int cy = _y + D(LENGTH / 2);

	int dx = x - cx;
	int dy = y - cy;

	// Button
	if (abs(dx) < D(10) && abs(dy) < D(10))
	{
		newMask |= (1 << static_cast<int>(EItem::Button));
	}

	// Directions
	if (dy < -D(15))
		newMask |= (1 << (int)EItem::Up);
	else if (dy > D(15))
		newMask |= (1 << (int)EItem::Down);

	if (dx < -D(15))
		newMask |= (1 << (int)EItem::Left);
	else if (dx > D(15))
		newMask |= (1 << (int)EItem::Right);

	if (newMask != _pressedItems)
	{
		_pressedItems = newMask;
		UpdateMcp23017();
	}
}

void GdiAtariJoystick::OnMouseMove(int x, int y)
{
	if (_pressedItems == 0)
		return;

	int cx = _x + D(WIDTH / 2);
	int cy = _y + D(LENGTH / 2);

	int dx = x - cx;
	int dy = y - cy;

	uint8_t newMask = 0;

	// Button drag
	if (abs(dx) < D(10) && abs(dy) < D(10))
		newMask |= (1 << (int)EItem::Button);

	// Direction drag
	if (dy < -D(15))
		newMask |= (1 << (int)EItem::Up);
	else if (dy > D(15))
		newMask |= (1 << (int)EItem::Down);

	if (dx < -D(15))
		newMask |= (1 << (int)EItem::Left);
	else if (dx > D(15))
		newMask |= (1 << (int)EItem::Right);

	_pressedItems = newMask;
	UpdateMcp23017();
}

void GdiAtariJoystick::OnMouseUp(int x, int y)
{
	_pressedItems = 0;
	UpdateMcp23017();
}

//void GdiAtariJoystick::Update(HDC * hdc)
//{
//	// Draw the joystick base
//	HBRUSH brushMain = CreateSolidBrush(RGB(128, 128, 128));
//	RECT rectMain{ _x, _y, _x + D(WIDTH), _y + D(LENGTH) };
//	FillRect(*hdc, &rectMain, brushMain);
//	DeleteObject(brushMain);
//
//	// Highlight colors
//	COLORREF colUp = RGB(255, 0, 0);
//	COLORREF colDown = RGB(255, 128, 0);
//	COLORREF colLeft = RGB(0, 128, 255);
//	COLORREF colRight = RGB(0, 255, 0);
//	COLORREF colBtn = RGB(255, 255, 0);
//
//	// Center
//	int cx = _x + D(WIDTH / 2);
//	int cy = _y + D(LENGTH / 2);
//
//	// Highlight UP
//	if (_pressedItems & (1 << (int)EItem::Up))
//	{
//		HBRUSH b = CreateSolidBrush(colUp);
//		RECT r{ cx - D(15), _y, cx + D(15), cy - D(20) };
//		FillRect(*hdc, &r, b);
//		DeleteObject(b);
//	}
//
//	// Highlight DOWN
//	if (_pressedItems & (1 << (int)EItem::Down))
//	{
//		HBRUSH b = CreateSolidBrush(colDown);
//		RECT r{ cx - D(15), cy + D(20), cx + D(15), _y + D(LENGTH) };
//		FillRect(*hdc, &r, b);
//		DeleteObject(b);
//	}
//
//	// Highlight LEFT
//	if (_pressedItems & (1 << (int)EItem::Left))
//	{
//		HBRUSH b = CreateSolidBrush(colLeft);
//		RECT r{ _x, cy - D(15), cx - D(20), cy + D(15) };
//		FillRect(*hdc, &r, b);
//		DeleteObject(b);
//	}
//
//	// Highlight RIGHT
//	if (_pressedItems & (1 << (int)EItem::Right))
//	{
//		HBRUSH b = CreateSolidBrush(colRight);
//		RECT r{ cx + D(20), cy - D(15), _x + D(WIDTH), cy + D(15) };
//		FillRect(*hdc, &r, b);
//		DeleteObject(b);
//	}
//
//	// Highlight BUTTON (center circle)
//	if (_pressedItems & (1 << (int)EItem::Button))
//	{
//		HBRUSH b = CreateSolidBrush(colBtn);
//		HBRUSH old = (HBRUSH)SelectObject(*hdc, b);
//
//		Ellipse(*hdc,
//			cx - D(12),
//			cy - D(12),
//			cx + D(12),
//			cy + D(12));
//
//		SelectObject(*hdc, old);
//		DeleteObject(b);
//	}
//}

void GdiAtariJoystick::Update(HDC* hdc)
{
	const int cellW = D(WIDTH) / 3;
	const int cellH = D(LENGTH) / 3;

	auto drawTriangle = [&](int cx, int cy, COLORREF color, const POINT pts[3])
		{
			HBRUSH brush = CreateSolidBrush(color);
			HPEN pen = CreatePen(PS_SOLID, 1, color);

			HBRUSH oldBrush = (HBRUSH)SelectObject(*hdc, brush);
			HPEN oldPen = (HPEN)SelectObject(*hdc, pen);

			Polygon(*hdc, pts, 3);

			SelectObject(*hdc, oldBrush);
			SelectObject(*hdc, oldPen);

			DeleteObject(brush);
			DeleteObject(pen);
		};

	auto drawCircle = [&](int cx, int cy, COLORREF color)
		{
			int x1 = _x + cx * cellW + cellW / 4;
			int y1 = _y + cy * cellH + cellH / 4;
			int x2 = _x + (cx + 1) * cellW - cellW / 4;
			int y2 = _y + (cy + 1) * cellH - cellH / 4;

			HBRUSH brush = CreateSolidBrush(color);
			HPEN pen = CreatePen(PS_SOLID, 1, color);

			HBRUSH oldBrush = (HBRUSH)SelectObject(*hdc, brush);
			HPEN oldPen = (HPEN)SelectObject(*hdc, pen);

			Ellipse(*hdc, x1, y1, x2, y2);

			SelectObject(*hdc, oldBrush);
			SelectObject(*hdc, oldPen);

			DeleteObject(brush);
			DeleteObject(pen);
		};

	auto colorFor = [&](bool active)
		{
			return active ? RGB(0, 200, 0) : RGB(140, 140, 140);
		};

	bool up = (_pressedItems & 0x01);
	bool down = (_pressedItems & 0x02);
	bool left = (_pressedItems & 0x04);
	bool right = (_pressedItems & 0x08);
	bool button = (_pressedItems & 0x10);

	// UP
	{
		POINT pts[3] = {
			 { _x + cellW * 1 + cellW / 2, _y + cellH * 0 + cellH / 4 },
			 { _x + cellW * 1 + cellW / 4, _y + cellH * 0 + cellH * 3 / 4 },
			 { _x + cellW * 1 + cellW * 3 / 4, _y + cellH * 0 + cellH * 3 / 4 }
		};
		drawTriangle(1, 0, colorFor(up), pts);
	}

	// DOWN
	{
		POINT pts[3] = {
			 { _x + cellW * 1 + cellW / 2, _y + cellH * 2 + cellH * 3 / 4 },
			 { _x + cellW * 1 + cellW / 4, _y + cellH * 2 + cellH / 4 },
			 { _x + cellW * 1 + cellW * 3 / 4, _y + cellH * 2 + cellH / 4 }
		};
		drawTriangle(1, 2, colorFor(down), pts);
	}

	// LEFT
	{
		POINT pts[3] = {
			 { _x + cellW * 0 + cellW / 4, _y + cellH * 1 + cellH / 2 },
			 { _x + cellW * 0 + cellW * 3 / 4, _y + cellH * 1 + cellH / 4 },
			 { _x + cellW * 0 + cellW * 3 / 4, _y + cellH * 1 + cellH * 3 / 4 }
		};
		drawTriangle(0, 1, colorFor(left), pts);
	}

	// RIGHT
	{
		POINT pts[3] = {
			 { _x + cellW * 2 + cellW * 3 / 4, _y + cellH * 1 + cellH / 2 },
			 { _x + cellW * 2 + cellW / 4, _y + cellH * 1 + cellH / 4 },
			 { _x + cellW * 2 + cellW / 4, _y + cellH * 1 + cellH * 3 / 4 }
		};
		drawTriangle(2, 1, colorFor(right), pts);
	}

	// CENTER BUTTON
	drawCircle(1, 1, colorFor(button));
}

void GdiAtariJoystick::UpdateMcp23017()
{
	uint16_t mask = 0;
	if (_joystickId == EId::Player1)
	{
		_windowsMcp23017.SimulateSetGpioPin(PinIoMappings::PLAYER_1_UP_PORT, PinIoMappings::PLAYER_1_UP_PIN, (_pressedItems & (1 << (int)EItem::Up )? 1 : 0));
		_windowsMcp23017.SimulateSetGpioPin(PinIoMappings::PLAYER_1_DOWN_PORT, PinIoMappings::PLAYER_1_DOWN_PIN, (_pressedItems & (1 << (int)EItem::Down )? 1 : 0));
		_windowsMcp23017.SimulateSetGpioPin(PinIoMappings::PLAYER_1_LEFT_PORT, PinIoMappings::PLAYER_1_LEFT_PIN, (_pressedItems & (1 << (int)EItem::Left )? 1 : 0));
		_windowsMcp23017.SimulateSetGpioPin(PinIoMappings::PLAYER_1_RIGHT_PORT, PinIoMappings::PLAYER_1_RIGHT_PIN, (_pressedItems & (1 << (int)EItem::Right )? 1 : 0));
		_windowsMcp23017.SimulateSetGpioPin(PinIoMappings::PLAYER_1_BUTTON_PORT, PinIoMappings::PLAYER_1_BUTTON_PIN, (_pressedItems & (1 << (int)EItem::Button )? 1 : 0));
	}
	else if (_joystickId == EId::Player2)
	{
		_windowsMcp23017.SimulateSetGpioPin(PinIoMappings::PLAYER_2_UP_PORT, PinIoMappings::PLAYER_2_UP_PIN, (_pressedItems & (1 << (int)EItem::Up )? 1 : 0));
		_windowsMcp23017.SimulateSetGpioPin(PinIoMappings::PLAYER_2_DOWN_PORT, PinIoMappings::PLAYER_2_DOWN_PIN, (_pressedItems & (1 << (int)EItem::Down )? 1 : 0));
		_windowsMcp23017.SimulateSetGpioPin(PinIoMappings::PLAYER_2_LEFT_PORT, PinIoMappings::PLAYER_2_LEFT_PIN, (_pressedItems & (1 << (int)EItem::Left )? 1 : 0));
		_windowsMcp23017.SimulateSetGpioPin(PinIoMappings::PLAYER_2_RIGHT_PORT, PinIoMappings::PLAYER_2_RIGHT_PIN, (_pressedItems & (1 << (int)EItem::Right )? 1 : 0));
		_windowsMcp23017.SimulateSetGpioPin(PinIoMappings::PLAYER_2_BUTTON_PORT, PinIoMappings::PLAYER_2_BUTTON_PIN, (_pressedItems & (1 << (int)EItem::Button )? 1 : 0));
	}
}