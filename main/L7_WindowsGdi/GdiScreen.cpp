#include "GdiScreen.hpp"
#include "Components/GdiLcd2004.hpp"
#include "../L0_System/DeviceSettings.hpp"
#include "../L1_Composition/Context/DeviceModelsContext.hpp"
#include "../L1_Composition/Context/DeviceDriversContext.hpp"
#include "../L3_Messages/Types.hpp"
#include "../L4_DomainModels/LedStrips/LedStrips.hpp"
#include <windows.h>

const int DEVICE_X = 10;
const int DEVICE_Y = 10;
const int DEVICE_LENGTH = 550;
const int DEVICE_WIDTH = 180;

const int SYSTEM_BUTTON_X = DEVICE_X + 420;
const int SYSTEM_BUTTON_Y = DEVICE_Y + 40;

const int JOYSTICK_PLAYER_1_X = DEVICE_X + 10;
const int JOYSTICK_PLAYER_1_Y = DEVICE_Y + 210;
const int JOYSTICK_PLAYER_2_X = DEVICE_X + 440;
const int JOYSTICK_PLAYER_2_Y = DEVICE_Y + 210;

const int LCD_2004_DISPLAY_X = DEVICE_X + 220;
const int LCD_2004_DISPLAY_Y = DEVICE_Y + 10;

const int PAUSE_LED_X = DEVICE_X + 160;
const int PAUSE_LED_Y = DEVICE_Y + 100;
const int SELECT_LED_X = DEVICE_X + 260;
const int SELECT_LED_Y = DEVICE_Y + 100;
const int SETUP_LED_X = DEVICE_X + 360;
const int SETUP_LED_Y = DEVICE_Y + 100;
const int PLAYER_1_LED_X = DEVICE_X + 200;
const int PLAYER_1_LED_Y = DEVICE_Y + 50;
const int PLAYER_2_LED_X = DEVICE_X + 800;
const int PLAYER_2_LED_Y = DEVICE_Y + 50;

const int SEVEN_DIGITS_DISPLAY_CENTRAL_PANEL_X = DEVICE_X + 160;
const int SEVEN_DIGITS_DISPLAY_CENTRAL_PANEL_Y = DEVICE_Y + 10;
const int SEVEN_DIGITS_DISPLAY_PLAYER1_X = DEVICE_X + 10;
const int SEVEN_DIGITS_DISPLAY_PLAYER1_Y = DEVICE_Y + 10;
const int SEVEN_DIGITS_DISPLAY_PLAYER2_X = DEVICE_X + 450;
const int SEVEN_DIGITS_DISPLAY_PLAYER2_Y = DEVICE_Y + 10;

const int LED_STRIPS_X = DEVICE_X + 20;
const int LED_STRIPS_Y = DEVICE_Y + 70;

GdiScreen::GdiScreen(
    DeviceModelsContext& deviceModelsContext,
    DeviceDriversContext& deviceDriversContext)
:   _hwnd(nullptr),
    _memDC(nullptr),
    _memBitmap(nullptr),
    _gdiSystemButton("SYSTEM", DeviceSettings::MCP23017_BIT_SYSTEM_BUTTON, 
        D(SYSTEM_BUTTON_X), D(SYSTEM_BUTTON_Y),
        deviceDriversContext.GetMcp23017DeviceDriver()),
    _gdiAtariJoystickPlayer1(Types::EJoystickId::Player1, 
        DeviceSettings::MCP23017_BIT_PLAYER_1_JOYSTICK_UP,
        DeviceSettings::MCP23017_BIT_PLAYER_1_JOYSTICK_RIGHT,
        DeviceSettings::MCP23017_BIT_PLAYER_1_JOYSTICK_DOWN,
        DeviceSettings::MCP23017_BIT_PLAYER_1_JOYSTICK_LEFT,
        DeviceSettings::MCP23017_BIT_PLAYER_1_JOYSTICK_BUTTON,
        D(JOYSTICK_PLAYER_2_X), D(JOYSTICK_PLAYER_2_Y),
        deviceDriversContext.GetMcp23017DeviceDriver()),
    _gdiAtariJoystickPlayer2(Types::EJoystickId::Player2,
        DeviceSettings::MCP23017_BIT_PLAYER_2_JOYSTICK_UP,
        DeviceSettings::MCP23017_BIT_PLAYER_2_JOYSTICK_RIGHT,
        DeviceSettings::MCP23017_BIT_PLAYER_2_JOYSTICK_DOWN,
        DeviceSettings::MCP23017_BIT_PLAYER_2_JOYSTICK_LEFT,
        DeviceSettings::MCP23017_BIT_PLAYER_2_JOYSTICK_BUTTON,
        D(JOYSTICK_PLAYER_2_X), D(JOYSTICK_PLAYER_2_Y)),
        deviceDriversContext.GetMcp23017DeviceDriver()),
    _gdiLcd2004(D(LCD_2004_DISPLAY_X), D(LCD_2004_DISPLAY_Y), deviceModelsContext.GetLcd2004DeviceModel()),
    _gdiTm1637CentralPanel(true, D(SEVEN_DIGITS_DISPLAY_CENTRAL_PANEL_X), D(SEVEN_DIGITS_DISPLAY_CENTRAL_PANEL_Y),
        deviceModelsContext.GetTm1637DeviceModelCentralPanel()),
    _gdiTm1637Player1(false, D(SEVEN_DIGITS_DISPLAY_PLAYER1_X), D(SEVEN_DIGITS_DISPLAY_PLAYER1_Y),
        deviceModelsContext.GetTm1637DeviceModelPlayer1()),
    _gdiTm1637Player2(false, D(SEVEN_DIGITS_DISPLAY_PLAYER2_X), D(SEVEN_DIGITS_DISPLAY_PLAYER2_Y),
        deviceModelsContext.GetTm1637DeviceModelPlayer2()),
    _gdiLedStrips(D(LED_STRIPS_X), D(LED_STRIPS_Y), deviceModelsContext.GetWs28xxDeviceModel()),
    _gdiPauseLed("Pause", GdiLed::EColor::Green, DeviceSettings::MCP23017_BIT_SELECT_LED,
        PAUSE_LED_X, PAUSE_LED_Y, deviceModelsContext.GetMcp23017DeviceModel()),
    _gdiSelectLed("Select", GdiLed::EColor::Green, DeviceSettings::MCP23017_BIT_SELECT_LED,
        SELECT_LED_X, SELECT_LED_Y, deviceModelsContext.GetMcp23017DeviceModel()),
    _gdiSetupLed("Setup", GdiLed::EColor::Green, DeviceSettings::MCP23017_BIT_SETUP_LED,
        SETUP_LED_X, SETUP_LED_Y, deviceModelsContext.GetMcp23017DeviceModel()),
    _gdiPlayer1Led("Player1", GdiLed::EColor::Green,
        DeviceSettings::MCP23017_BIT_PLAYER_1_LED, PLAYER_1_LED_X, PLAYER_1_LED_Y, 
        deviceModelsContext.GetMcp23017DeviceModel()),
    _gdiPlayer2Led("Player2", GdiLed::EColor::Green,
        DeviceSettings::MCP23017_BIT_PLAYER_2_LED, PLAYER_2_LED_X, PLAYER_2_LED_Y, 
        deviceModelsContext.GetMcp23017DeviceModel())
{
    _enclosureBrush = CreateSolidBrush(RGB(100, 100, 100));
    _gdiMouseInputs.emplace_back(&_gdiSystemButton);


}

GdiScreen::~GdiScreen()
{
    DeleteObject(_enclosureBrush);
}

uint16_t GdiScreen::D(
    uint16_t value)  const
{
    return value * 2; 
}

HDC GdiScreen::GetMemDc()
{
    return _memDC;
}

void GdiScreen::CreateMemoryDc(
    HWND hwnd, 
    uint16_t width,
    uint16_t height)
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

    HDC screenDC = GetDC(nullptr);
    _memDC = CreateCompatibleDC(screenDC);
    _memBitmap = CreateCompatibleBitmap(screenDC, width, height);
    SelectObject(_memDC, _memBitmap);
    ReleaseDC(nullptr, screenDC);
}

void GdiScreen::OnMouseDown(
    uint16_t x, 
    uint16_t y)
{
	for (auto& mouseInput : _gdiMouseInputs)
	{
		mouseInput->OnMouseDown(x, y);
        mouseInput->Update(&_memDC);
	}
}

void GdiScreen::OnMouseMove(
    uint16_t x, 
    uint16_t y)
{
	for (auto& mouseInput : _gdiMouseInputs)
	{
		mouseInput->OnMouseMove(x, y);
        mouseInput->Update(&_memDC);
	}
}

void GdiScreen::OnMouseUp(
    uint16_t x, 
    uint16_t y)
{
    for (auto& mouseInput : _gdiMouseInputs)
    {
        mouseInput->OnMouseUp(x, y);
        mouseInput->Update(&_memDC);
    }
}

/// @brief Update entire screen.
/// Update everything is needed to make sure that parts are not only updated when they get an update 
/// due to a WM_... message.
void GdiScreen::Update()
{
    UpdateEnclosure();
    UpdateLcd2004();
    UpdateMcp23017Input();
    UpdateMcp23017Output();
    UpdateTm1637CentralPanel();
    UpdateTm1637Player1();
    UpdateTm1637Player2();
    UpdateLedStrips();
}

void GdiScreen::UpdateEnclosure()
{
    RECT rect = { D(DEVICE_X), D(DEVICE_Y), D(DEVICE_X + DEVICE_LENGTH), D(DEVICE_Y + DEVICE_WIDTH) };
    FillRect(_memDC, &rect, _enclosureBrush);
    auto oldBrush = (HBRUSH)SelectObject(_memDC, _enclosureBrush);
    SetTextColor(_memDC, RGB(100, 0, 0));
    TextOut(_memDC, D(350), D(50), L"FRAXIS", (int)wcslen(L"FRAXIS"));
    SelectObject(_memDC, oldBrush);
}

void GdiScreen::UpdateLcd2004()
{
    _gdiLcd2004.Update(&_memDC);
}

void GdiScreen::UpdateMcp23017Input()
{
    for (const auto& mouseInput : _gdiMouseInputs)
	{
		mouseInput->Update(&_memDC);
	}
}

void GdiScreen::UpdateMcp23017Output()
{
    _gdiPauseLed.Update(&_memDC);
    _gdiSelectLed.Update(&_memDC);
    _gdiSetupLed.Update(&_memDC);
    _gdiPlayer1Led.Update(&_memDC);
    _gdiPlayer2Led.Update(&_memDC);
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
