#include "GdiScreen.hpp"
#include "Components/GdiButton.hpp"
#include "Components/GdiLed.hpp"
#include "Components/GdiAtariJoystick.hpp"
#include <windows.h>
#include "Components/WindowsMcp23017.hpp"
#include "Components/WindowsTm1637.hpp"
#include "Components/GdiLcd1602Display.hpp"
#include "../Core/Components/PinIoMappings.hpp"

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

const int PAUSE_LED_X = DEVICE_X + 160;
const int PAUSE_LED_Y = DEVICE_Y + 100;
const int PAUSE_LED_WIDTH = 20;
const int PAUSE_LED_HEIGHT = 20;

const int SELECT_LED_X = DEVICE_X + 260;
const int SELECT_LED_Y = DEVICE_Y + 100;
const int SELECT_LED_WIDTH = 20;
const int SELECT_LED_HEIGHT = 20;

const int SETUP_LED_X = DEVICE_X + 360;
const int SETUP_LED_Y = DEVICE_Y + 100;
const int SETUP_LED_WIDTH = 20;
const int SETUP_LED_HEIGHT = 20;

const int PLAYER_1_LED_X = DEVICE_X + 200;
const int PLAYER_1_LED_Y = DEVICE_Y + 50;
const int PLAYER_1_LED_WIDTH = 20;
const int PLAYER_1_LED_HEIGHT = 20;

const int PLAYER_2_LED_X = DEVICE_X + 840;
const int PLAYER_2_LED_Y = DEVICE_Y + 50;
const int PLAYER_2_LED_WIDTH = 20;
const int PLAYER_2_LED_HEIGHT = 20;

GdiScreen::GdiScreen(
    WindowsLedStripDriver* windowsLedStripDriver,
    PinIo* pinIo,
    WindowsMcp23017* windowsMcp23017,
    WindowsLcd1602Display* lcdDisplay,
    WindowsTm1637* tm1637CentralPanel,
    WindowsTm1637* tm1637Player1,
    WindowsTm1637* tm1637Player2)
    : _windowsLedStripDriver(*windowsLedStripDriver),
    _pinIo(*pinIo),
    _windowsMcp23017(*windowsMcp23017),
    _lcdDisplay(*lcdDisplay),
    _gdiLedStrips(*this, *windowsLedStripDriver, D(LED_STRIPS_X), D(LED_STRIPS_Y)),
    _gdiLcd1602Display(*this, *lcdDisplay, D(LCD_1602_DISPLAY_X), D(LCD_1602_DISPLAY_Y)),
    _gdiSevenDigitsDisplayCentralPanel(*this, *tm1637CentralPanel, 4, false,
        D(SEVEN_DIGITS_DISPLAY_CENTRAL_PANEL_X),
        D(SEVEN_DIGITS_DISPLAY_CENTRAL_PANEL_Y)),
    _gdiSevenDigitsDisplayPlayer1(*this, *tm1637Player1, 6, true,
        D(SEVEN_DIGITS_DISPLAY_PLAYER1_X),
        D(SEVEN_DIGITS_DISPLAY_PLAYER1_Y)),
    _gdiSevenDigitsDisplayPlayer2(*this, *tm1637Player2, 6, false,
        D(SEVEN_DIGITS_DISPLAY_PLAYER2_X),
        D(SEVEN_DIGITS_DISPLAY_PLAYER2_Y)),
    _gdiPauseLed(*pinIo, *windowsMcp23017, PinIoMappings::EIdBit::PauseLed,
        *this, PAUSE_LED_X, PAUSE_LED_Y, PAUSE_LED_WIDTH, PAUSE_LED_HEIGHT,
        "Pause", RGB(0, 50, 0), RGB(0, 255, 0)),
    _gdiSelectLed(*pinIo, *windowsMcp23017, PinIoMappings::EIdBit::SelectLed,
        *this, SELECT_LED_X, SELECT_LED_Y, SELECT_LED_WIDTH, SELECT_LED_HEIGHT,
        "Select", RGB(0, 50, 0), RGB(0, 255, 0)),
    _gdiSetupLed(*pinIo, *windowsMcp23017, PinIoMappings::EIdBit::SetupLed,
        *this, SETUP_LED_X, SETUP_LED_Y, SETUP_LED_WIDTH, SETUP_LED_HEIGHT,
        "Setup", RGB(50, 0, 0), RGB(255, 0, 0)),
    _gdiPlayer1Led(*pinIo, *windowsMcp23017, PinIoMappings::EIdBit::Player1Led,
        *this, PLAYER_1_LED_X, PLAYER_1_LED_Y, PLAYER_1_LED_WIDTH, PLAYER_1_LED_HEIGHT,
        "P1", RGB(0, 50, 0), RGB(0, 255, 0)),
    _gdiPlayer2Led(*pinIo, *windowsMcp23017, PinIoMappings::EIdBit::Player2Led,
        *this, PLAYER_2_LED_X, PLAYER_2_LED_Y, PLAYER_2_LED_WIDTH, PLAYER_2_LED_HEIGHT,
        "P2", RGB(0, 50, 0), RGB(0, 255, 0))
{
	// Joystick Player 1
	_gdiMouseInputs.emplace_back(
		 new GdiAtariJoystick(
			  GdiAtariJoystick::EId::Player1,
			 *pinIo,
			 *windowsMcp23017,
			  *this,
			  D(JOYSTICK_PLAYER1_X),
			  D(JOYSTICK_PLAYER1_Y)
		 )
	);

	// Joystick Player 2
	_gdiMouseInputs.emplace_back(
		new GdiAtariJoystick(
			GdiAtariJoystick::EId::Player2,
			*pinIo,
			*windowsMcp23017,
			*this,
			D(JOYSTICK_PLAYER2_X),
			D(JOYSTICK_PLAYER2_Y)
		)
	);

	_gdiMouseInputs.emplace_back(
		new GdiButton(
			*windowsMcp23017,
            PinIoMappings::EIdBit::SystemButton,
			*this,
			D(SYSTEM_BUTTON_X),
			D(SYSTEM_BUTTON_Y),
			D(SYSTEM_BUTTON_WIDTH),
			D(SYSTEM_BUTTON_HEIGHT)
		)
	);
}

void GdiScreen::CreateMemoryDc(HWND hwnd, int width, int height)
{
    _hwnd = hwnd;
	HDC hdc = GetDC(hwnd);
	_memDC = CreateCompatibleDC(hdc);
	_memBitmap = CreateCompatibleBitmap(hdc, width, height);
	SelectObject(_memDC, _memBitmap);
	ReleaseDC(hwnd, hdc);
}

void GdiScreen::Update()
{
	HBRUSH brush = CreateSolidBrush(RGB(100, 100, 100));
	RECT rect = { D(DEVICE_X), D(DEVICE_Y), D(DEVICE_X + DEVICE_LENGTH), D(DEVICE_Y + DEVICE_WIDTH) };
	FillRect(_memDC, &rect, brush);

	// Draw text
    SetTextColor(_memDC, RGB(100, 0, 0));
	TextOut(_memDC, D(350), D(50), L"FRAXIS", (int) wcslen(L"FRAXIS"));

	_gdiLedStrips.Update(&_memDC);
	_gdiLcd1602Display.Update(&_memDC);
	_gdiSevenDigitsDisplayCentralPanel.Update(&_memDC);
	_gdiSevenDigitsDisplayPlayer1.Update(&_memDC);
	_gdiSevenDigitsDisplayPlayer2.Update(&_memDC);
    
    _gdiPauseLed.Update(&_memDC);
    _gdiSelectLed.Update(&_memDC);
    _gdiSetupLed.Update(&_memDC);
    _gdiPlayer1Led.Update(&_memDC);
    _gdiPlayer2Led.Update(&_memDC);

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
		mouseInput->OnMouseDown(x, y);
	}
}

void GdiScreen::OnMouseMove(int x, int y)
{
	for (auto& mouseInput : _gdiMouseInputs)
	{
		mouseInput->OnMouseMove(x, y);
	}
}

void GdiScreen::OnMouseUp(int x, int y)
{
	for (auto& mouseInput : _gdiMouseInputs)
	{
		mouseInput->OnMouseUp(x, y);
	}
}
