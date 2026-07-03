#include "GdiScreen.hpp"
#include "Components/GdiButton.hpp"
#include "Components/GdiAtariJoystick.hpp"
#include <windows.h>
#include "../Core/Menu/MenuSimulator.hpp"
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

GdiScreen::GdiScreen(PinIo& pinIo, WindowsMcp23017& windowsMcp23017, WindowsLcd1602Display& lcdDisplay,
	WindowsTm1637& tm1637CentralPanel, WindowsTm1637& tm1637Player1, WindowsTm1637& tm1637Player2, 
	MenuSimulator& menuSimulator)
	: _pinIo(pinIo), 
	  _windowsMcp23017(windowsMcp23017),
	  _lcdDisplay(lcdDisplay),
	  _menuSimulator(menuSimulator),
	  _gdiLedStrips(*this, D(LED_STRIPS_X), D(LED_STRIPS_Y)),
	  _gdiLcd1602Display(*this, _lcdDisplay, D(LCD_1602_DISPLAY_X), D(LCD_1602_DISPLAY_Y)),
	  _gdiSevenDigitsDisplayCentralPanel(
		   *this, tm1637CentralPanel, 4, false, D(SEVEN_DIGITS_DISPLAY_CENTRAL_PANEL_X), D(SEVEN_DIGITS_DISPLAY_CENTRAL_PANEL_Y)),
	  _gdiSevenDigitsDisplayPlayer1(
		  *this, tm1637Player1, 6, true, D(SEVEN_DIGITS_DISPLAY_PLAYER1_X), D(SEVEN_DIGITS_DISPLAY_PLAYER1_Y)),
	  _gdiSevenDigitsDisplayPlayer2(
		  *this, tm1637Player2, 6, false, D(SEVEN_DIGITS_DISPLAY_PLAYER2_X), D(SEVEN_DIGITS_DISPLAY_PLAYER2_Y))
{
	// Joystick Player 1
	_gdiMouseInputs.emplace_back(
		 new GdiAtariJoystick(
			  GdiAtariJoystick::EId::Player1,
			 pinIo,
			 windowsMcp23017,
			  *this,
			  D(JOYSTICK_PLAYER1_X),
			  D(JOYSTICK_PLAYER1_Y)
		 )
	);

	// Joystick Player 2
	_gdiMouseInputs.emplace_back(
		new GdiAtariJoystick(
			GdiAtariJoystick::EId::Player2,
			pinIo,
			windowsMcp23017,
			*this,
			D(JOYSTICK_PLAYER2_X),
			D(JOYSTICK_PLAYER2_Y)
		)
	);

	_gdiMouseInputs.emplace_back(
		new GdiButton(
			windowsMcp23017,
            PinIoMappings::EIdBit::SystemButton,
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

    // LED TRY
    int x = 80;
    int y = 120;
    
     // Sizes (tweak to taste)
    const int bezelRadius = 12;   // outer ring
    const int ledRadius = 9;   // inner LED

    // Outer bezel (dark ring)
    HBRUSH bezelBrush = CreateSolidBrush(RGB(80, 80, 80));
    HBRUSH oldBrush = (HBRUSH)SelectObject(_memDC, bezelBrush);
    HPEN   bezelPen = CreatePen(PS_SOLID, 1, RGB(20, 20, 20));
    HPEN   oldPen = (HPEN)SelectObject(_memDC, bezelPen);

    Ellipse(_memDC,
        x - bezelRadius, y - bezelRadius,
        x + bezelRadius, y + bezelRadius);

    // LED lens

    HBRUSH ledBrush = CreateSolidBrush(RGB(255, 0, 0)); // RED
    SelectObject(_memDC, ledBrush);

    Ellipse(_memDC,
        x - ledRadius, y - ledRadius,
        x + ledRadius, y + ledRadius);


    // Cleanup
    SelectObject(_memDC, oldBrush);
    SelectObject(_memDC, oldPen);
    DeleteObject(bezelBrush);
    DeleteObject(bezelPen);
    DeleteObject(ledBrush);

    HFONT hFont = CreateFontA(
        24, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE,
        ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
        DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE,
        "DSEG7 Classic Mono"   // or any font you want
    );

    HFONT oldFont = (HFONT)SelectObject(_memDC, hFont);

    SetTextColor(_memDC, RGB(200, 200, 200));
    TextOut(_memDC, x + 15, y - 12, L"Select", (int)wcslen(L"Select"));

    SelectObject(_memDC, oldFont);
    DeleteObject(hFont);

    // END LED TRY

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
		//if (mouseInput->HitTest(x, y))
		//{
			mouseInput->OnMouseDown(x, y);
		//}
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
		//if (mouseInput->HitTest(x, y))
		{
			mouseInput->OnMouseUp(x, y);
		}
	}
}
