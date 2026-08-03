#include "GdiScreen.hpp"
#include "Components/GdiLcd2004.hpp"
#include "../L1_Composition/Context/DeviceModelsContext.hpp"
#include "../L4_DomainModels/LedStrips/LedStrips.hpp"
#include <windows.h>

const int DEVICE_X = 10;
const int DEVICE_Y = 10;
const int DEVICE_LENGTH = 550;
const int DEVICE_WIDTH = 180;

const int LCD_2004_DISPLAY_X = DEVICE_X + 220;
const int LCD_2004_DISPLAY_Y = DEVICE_Y + 10;

const int SEVEN_DIGITS_DISPLAY_CENTRAL_PANEL_X = DEVICE_X + 160;
const int SEVEN_DIGITS_DISPLAY_CENTRAL_PANEL_Y = DEVICE_Y + 10;
const int SEVEN_DIGITS_DISPLAY_PLAYER1_X = DEVICE_X + 10;
const int SEVEN_DIGITS_DISPLAY_PLAYER1_Y = DEVICE_Y + 10;
const int SEVEN_DIGITS_DISPLAY_PLAYER2_X = DEVICE_X + 450;
const int SEVEN_DIGITS_DISPLAY_PLAYER2_Y = DEVICE_Y + 10;

const int LED_STRIPS_X = DEVICE_X + 20;
const int LED_STRIPS_Y = DEVICE_Y + 70;

GdiScreen::GdiScreen(
    DeviceModelsContext& deviceModelsContext)
:   _hwnd(nullptr), _memDC(nullptr), _memBitmap(nullptr),
    _gdiLcd2004(D(LCD_2004_DISPLAY_X), D(LCD_2004_DISPLAY_Y), deviceModelsContext.GetLcd2004DeviceModel()),
    _gdiTm1637CentralPanel(true, D(SEVEN_DIGITS_DISPLAY_CENTRAL_PANEL_X), D(SEVEN_DIGITS_DISPLAY_CENTRAL_PANEL_Y),
        deviceModelsContext.GetTm1637DeviceModelCentralPanel()),
    _gdiTm1637Player1(false, D(SEVEN_DIGITS_DISPLAY_PLAYER1_X), D(SEVEN_DIGITS_DISPLAY_PLAYER1_Y),
        deviceModelsContext.GetTm1637DeviceModelPlayer1()),
    _gdiTm1637Player2(false, D(SEVEN_DIGITS_DISPLAY_PLAYER2_X), D(SEVEN_DIGITS_DISPLAY_PLAYER2_Y),
        deviceModelsContext.GetTm1637DeviceModelPlayer2()),
    _gdiLedStrips(LedStrips::NUMBER_OF_LED_STRIPS, LedStrips::NUMBER_OF_LEDS_PER_LED_STRIP,
        D(LED_STRIPS_X), D(LED_STRIPS_Y), deviceModelsContext.GetWs28xxDeviceModel())
{
    _enclosureBrush = CreateSolidBrush(RGB(100, 100, 100));
}

GdiScreen::~GdiScreen()
{
    DeleteObject(_enclosureBrush);
}

int GdiScreen::D(int value) 
{
    return value * 2; 
}

HDC GdiScreen::GetMemDc()
{
    return _memDC;
}

void GdiScreen::CreateMemoryDc(HWND hwnd, int width, int height)
{
    _hwnd = hwnd;

    if (_memBitmap)
    {
        DeleteObject(_memBitmap);
        _memBitmap = nullptr;
    }

    if (_memDC)
    {
        DeleteDC(_memDC);
        _memDC = nullptr;
    }

    HDC screenDC = GetDC(NULL);
    _memDC = CreateCompatibleDC(screenDC);
    _memBitmap = CreateCompatibleBitmap(screenDC, width, height);
    SelectObject(_memDC, _memBitmap);
    ReleaseDC(NULL, screenDC);
}

/// @brief Update entire screen.
/// Update everything is needed to make sure that parts are not only updated when they get an update 
/// due to a WM_... message.
void GdiScreen::Update()
{
    UpdateEnclosure();
    UpdateLcd2004();
    UpdateTm1637CentralPanel();
    UpdateTm1637Player1();
    UpdateTm1637Player2();
    UpdateLedStrips();
}

void GdiScreen::UpdateEnclosure()
{
    RECT rect = { D(DEVICE_X), D(DEVICE_Y), D(DEVICE_X + DEVICE_LENGTH), D(DEVICE_Y + DEVICE_WIDTH) };
    FillRect(_memDC, &rect, _enclosureBrush);
    HBRUSH oldBrush = (HBRUSH)SelectObject(_memDC, _enclosureBrush);
    SetTextColor(_memDC, RGB(100, 0, 0));
    TextOut(_memDC, D(350), D(50), L"FRAXIS", (int)wcslen(L"FRAXIS"));
    SelectObject(_memDC, oldBrush);
}

void GdiScreen::UpdateLcd2004()
{
    _gdiLcd2004.Update(&_memDC);
}

void GdiScreen::UpdateTm1637CentralPanel()
{
    _gdiTm1637CentralPanel.Update(&_memDC);
}

void GdiScreen::UpdateTm1637Player1()
{
    _gdiTm1637Player1.Update(&_memDC);
}

void GdiScreen::UpdateTm1637Player2()
{
    _gdiTm1637Player2.Update(&_memDC);
}

void GdiScreen::UpdateLedStrips()
{
    _gdiLedStrips.Update(&_memDC);
}

//const int JOYSTICK_PLAYER1_X = DEVICE_X + 10;
//const int JOYSTICK_PLAYER1_Y = DEVICE_Y + 210;
//const int JOYSTICK_PLAYER2_X = DEVICE_X + 440;
//const int JOYSTICK_PLAYER2_Y = DEVICE_Y + 210;
//
//const int SYSTEM_BUTTON_X = DEVICE_X + 220;
//const int SYSTEM_BUTTON_Y = DEVICE_Y + 40;
//const int SYSTEM_BUTTON_WIDTH = 20;
//const int SYSTEM_BUTTON_HEIGHT = 20;
//
//const int PAUSE_LED_X = DEVICE_X + 160;
//const int PAUSE_LED_Y = DEVICE_Y + 100;
//const int PAUSE_LED_WIDTH = 20;
//const int PAUSE_LED_HEIGHT = 20;
//
//const int SELECT_LED_X = DEVICE_X + 260;
//const int SELECT_LED_Y = DEVICE_Y + 100;
//const int SELECT_LED_WIDTH = 20;
//const int SELECT_LED_HEIGHT = 20;
//
//const int SETUP_LED_X = DEVICE_X + 360;
//const int SETUP_LED_Y = DEVICE_Y + 100;
//const int SETUP_LED_WIDTH = 20;
//const int SETUP_LED_HEIGHT = 20;
//
//const int PLAYER_1_LED_X = DEVICE_X + 200;
//const int PLAYER_1_LED_Y = DEVICE_Y + 50;
//const int PLAYER_1_LED_WIDTH = 20;
//const int PLAYER_1_LED_HEIGHT = 20;
//
//const int PLAYER_2_LED_X = DEVICE_X + 840;
//const int PLAYER_2_LED_Y = DEVICE_Y + 50;
//const int PLAYER_2_LED_WIDTH = 20;
//const int PLAYER_2_LED_HEIGHT = 20;
//

//    //_gdiPauseLed(*pinIo, *windowsMcp23017, PinIoMappings::EIdBit::PauseLed,
//    //    *this, PAUSE_LED_X, PAUSE_LED_Y, PAUSE_LED_WIDTH, PAUSE_LED_HEIGHT,
//    //    "Pause", RGB(0, 50, 0), RGB(0, 255, 0)),
//    //_gdiPlayer1Led(*pinIo, *windowsMcp23017, PinIoMappings::EIdBit::Player1Led,
//    //    *this, PLAYER_1_LED_X, PLAYER_1_LED_Y, PLAYER_1_LED_WIDTH, PLAYER_1_LED_HEIGHT,
//    //    "P1", RGB(0, 50, 0), RGB(0, 255, 0)),
////{
//    // Joystick Player 1
//    //_gdiMouseInputs.emplace_back(
//    //    new GdiAtariJoystick(
//    //        GdiAtariJoystick::EId::Player1,
//    //        *pinIo,
//    //        *windowsMcp23017,
//    //        *this,
//    //        D(JOYSTICK_PLAYER1_X),
//    //        D(JOYSTICK_PLAYER1_Y)
//    //    )
//    //);
//
//
//	//_gdiMouseInputs.emplace_back(
//	//	new GdiButton(
//	//		*windowsMcp23017,
// //           PinIoMappings::EIdBit::SystemButton,
//	//		*this,
//	//		D(SYSTEM_BUTTON_X),
//	//		D(SYSTEM_BUTTON_Y),
//	//		D(SYSTEM_BUTTON_WIDTH),
//	//		D(SYSTEM_BUTTON_HEIGHT)
//	//	)
//	//);
//}
//
//void GdiScreen::Update()
//{
//    //if (_updateTm1637)
//    {
//        //_gdiSevenDigitsDisplayCentralPanel.Update(&_memDC);
//        //_gdiSevenDigitsDisplayPlayer1.Update(&_memDC);
//        //_gdiSevenDigitsDisplayPlayer2.Update(&_memDC);
//        _updateTm1637 = false;
//    }
//
//    _gdiPauseLed.Update(&_memDC);
//    _gdiSelectLed.Update(&_memDC);
//    _gdiSetupLed.Update(&_memDC);
//    _gdiPlayer1Led.Update(&_memDC);
//    _gdiPlayer2Led.Update(&_memDC);
//
//	for (const auto& mouseInput : _gdiMouseInputs)
//	{
//		mouseInput->Update(&_memDC);
//	}
//
//	DeleteObject(brush);
//}
//

//void GdiScreen::OnMouseDown(int x, int y)
//{
//	for (auto& mouseInput : _gdiMouseInputs)
//	{
//		mouseInput->OnMouseDown(x, y);
//	}
//}
//
//void GdiScreen::OnMouseMove(int x, int y)
//{
//	for (auto& mouseInput : _gdiMouseInputs)
//	{
//		mouseInput->OnMouseMove(x, y);
//	}
//}
//
//void GdiScreen::OnMouseUp(int x, int y)
//{
//	for (auto& mouseInput : _gdiMouseInputs)
//	{
//		mouseInput->OnMouseUp(x, y);
//	}
//}
