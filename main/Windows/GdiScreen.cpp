#include "GdiScreen.hpp"
#include "Components/GdiButton.hpp"
#include <windows.h>
#include "../Core/Menu/MenuSimulator.hpp"


const int DEVICE_X = 10;
const int DEVICE_Y = 10;
const int DEVICE_LENGTH = 550;
const int DEVICE_WIDTH = 180;

const int LCD_1602_DISPLAY_X = DEVICE_X + 220;
const int LCD_1602_DISPLAY_Y = DEVICE_Y + 10;

const int LED_STRIPS_X = DEVICE_X + 20;
const int LED_STRIPS_Y = DEVICE_Y + 70;	

const int SEVEN_DIGITS_DISPLAY_CENTRAL_PANEL_X = DEVICE_X + 160;
const int SEVEN_DIGITS_DISPLAY_CENTRAL_PANEL_Y = DEVICE_Y + 10;
const int SEVEN_DIGITS_DISPLAY_PLAYER1_X = DEVICE_X + 10;
const int SEVEN_DIGITS_DISPLAY_PLAYER1_Y = DEVICE_Y + 10;
const int SEVEN_DIGITS_DISPLAY_PLAYER2_X = DEVICE_X + 450;
const int SEVEN_DIGITS_DISPLAY_PLAYER2_Y = DEVICE_Y + 10;

const int JOYSTICK_PLAYER1_X = DEVICE_X + 10;
const int JOYSTICK_PLAYER1_Y = DEVICE_Y + 210;
const int JOYSTICK_PLAYER2_X = DEVICE_X + 440;
const int JOYSTICK_PLAYER2_Y = DEVICE_Y + 210;

const int SYSTEM_BUTTON_X = DEVICE_X + 220;
const int SYSTEM_BUTTON_Y = DEVICE_Y + 40;
const int SYSTEM_BUTTON_WIDTH = 20;
const int SYSTEM_BUTTON_HEIGHT = 20;

GdiScreen::GdiScreen(PinIo& pinIo, Lcd1602Display& lcdDisplay, MenuSimulator& menuSimulator)
	: _pinIo(pinIo), 
	  _lcdDisplay(lcdDisplay),
	  _menuSimulator(menuSimulator),
	  _gdiLedStrips(*this, D(LED_STRIPS_X), D(LED_STRIPS_Y)),
	  _gdiLcd1602Display(*this, _lcdDisplay, D(LCD_1602_DISPLAY_X), D(LCD_1602_DISPLAY_Y)),
	  _gdiSevenDigitsDisplayCentralPanel(
		   *this, 4, false, D(SEVEN_DIGITS_DISPLAY_CENTRAL_PANEL_X), D(SEVEN_DIGITS_DISPLAY_CENTRAL_PANEL_Y)),
	  _gdiSevenDigitsDisplayPlayer1(
		  *this, 6, true, D(SEVEN_DIGITS_DISPLAY_PLAYER1_X), D(SEVEN_DIGITS_DISPLAY_PLAYER1_Y)),
	  _gdiSevenDigitsDisplayPlayer2(
		  *this, 6, false, D(SEVEN_DIGITS_DISPLAY_PLAYER2_X), D(SEVEN_DIGITS_DISPLAY_PLAYER2_Y))
{
	// Joystick Player 1
	_gdiMouseInputs.emplace_back(
		 new GdiAtariJoystick(
			  pinIo,
			  GdiAtariJoystick::EId::Player1,
			  *this,
			  D(JOYSTICK_PLAYER1_X),
			  D(JOYSTICK_PLAYER1_Y)
		 )
	);

	// Joystick Player 2
	_gdiMouseInputs.emplace_back(
		new GdiAtariJoystick(
			GdiAtariJoystick::EId::Player2,
			*this,
			D(JOYSTICK_PLAYER2_X),
			D(JOYSTICK_PLAYER2_Y)
		)
	);

	_gdiMouseInputs.emplace_back(
		new GdiButton(
			*this,
			D(SYSTEM_BUTTON_X),
			D(SYSTEM_BUTTON_Y),
			D(SYSTEM_BUTTON_WIDTH),
			D(SYSTEM_BUTTON_HEIGHT)
		)
	);
}

GdiScreen::~GdiScreen()
{
}

void GdiScreen::CreateMemoryDc(HWND hwnd, int width, int height)
{
	HDC hdc = GetDC(hwnd);
	_memDC = CreateCompatibleDC(hdc);
	_memBitmap = CreateCompatibleBitmap(hdc, width, height);
	SelectObject(_memDC, _memBitmap);
	ReleaseDC(hwnd, hdc);
}

void GdiScreen::Update()
{
	HBRUSH brush = CreateSolidBrush(RGB(200, 200, 200));
	RECT rect = { D(DEVICE_X), D(DEVICE_Y), D(DEVICE_X + DEVICE_LENGTH), D(DEVICE_Y + DEVICE_WIDTH) };
	FillRect(_memDC, &rect, brush);

	// Draw text
	TextOut(_memDC, D(20), D(150), L"FRAXIS", (int) wcslen(L"FRAXIS"));

	_gdiLedStrips.Update(&_memDC);
	_gdiLcd1602Display.Update(&_memDC);
	_gdiSevenDigitsDisplayCentralPanel.Update(&_memDC);
	_gdiSevenDigitsDisplayPlayer1.Update(&_memDC);
	_gdiSevenDigitsDisplayPlayer2.Update(&_memDC);

	for (const auto& mouseInput : _gdiMouseInputs)
	{
		mouseInput->Update(&_memDC);
	}

	DeleteObject(brush);
}

void GdiScreen::OnMouseDown(int x, int y)
{
	for (auto& mouseInput : _gdiMouseInputs)
	{
		if (mouseInput->HitTest(x, y))
		{
			mouseInput->OnMouseDown(x, y);
			break;
		}
	}
}

void GdiScreen::OnMouseMove(int x, int y)
{
	for (auto& mouseInput : _gdiMouseInputs)
	{
		if (mouseInput->HitTest(x, y))
		{
			mouseInput->OnMouseMove(x, y);
			break;
		}
	}
}

void GdiScreen::OnMouseUp(int x, int y)
{
	for (auto& mouseInput : _gdiMouseInputs)
	{
		if (mouseInput->HitTest(x, y))
		{
			mouseInput->OnMouseUp(x, y);
			break;
		}
	}
}

void GdiScreen::OnJoystickChanged(GdiAtariJoystick::EId joystickId, uint8_t pressedItems)
{
	if (joystickId == GdiAtariJoystick::EId::Player1)
	{
		_menuSimulator.SetJoystickState(AtariJoystick::EId::Player1, pressedItems);
	}
	else if (joystickId == GdiAtariJoystick::EId::Player2	)
	{
		_menuSimulator.SetJoystickState(AtariJoystick::EId::Player2, pressedItems);
	}
}

void GdiScreen::OnSystemButtonChanged(bool pressed)
{
	_menuSimulator.SetSystemButtonState(pressed);
}