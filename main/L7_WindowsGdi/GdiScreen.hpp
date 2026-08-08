#pragma once

#include "IGdiMouseInput.hpp"
#include "Components/GdiButton.hpp"
#include "Components/GdiAtariJoystick.hpp"
#include "Components/GdiLcd2004.hpp"
#include "Components/GdiLed.hpp"
#include "Components/GdiTm1637.hpp"
#include "Components/GdiLedStrips.hpp"
#include <Windows.h>
#include <vector>
#include <memory>

class DeviceModelsContext;
class DeviceDriversContext;

class GdiScreen
{
public:
    GdiScreen();
    ~GdiScreen();

    HWND GetHwnd();
    HDC GetMemDc();

    void SetDeviceModels(
        DeviceModelsContext& deviceModelsContext);
    void SetDeviceDrivers(
        DeviceDriversContext& deviceDriversContext);

    void CreateMemoryDc(
        HWND hwnd, 
        uint16_t width,
        uint16_t height);

    void OnMouseDown(
        uint16_t x, 
        uint16_t y);
    void OnMouseMove(
        uint16_t x, 
        uint16_t y);
    void OnMouseUp(
        uint16_t x, 
        uint16_t y);
    void Update();

    void UpdateLcd2004();
    void UpdateMcp23017Input();
    void UpdateMcp23017Output();
    void UpdateTm1637CentralPanel();
    void UpdateTm1637Player1();
    void UpdateTm1637Player2();
    void UpdateLedStrips();

private:
    void UpdateEnclosure();

    std::vector<IGdiMouseInput*> _gdiMouseInputs;
    GdiButton       _gdiSystemButton;
    GdiAtariJoystick _gdiAtariJoystickPlayer1;
    GdiAtariJoystick _gdiAtariJoystickPlayer2;

    GdiLcd2004      _gdiLcd2004;
    GdiTm1637       _gdiTm1637CentralPanel;
    GdiTm1637       _gdiTm1637Player1;
    GdiTm1637       _gdiTm1637Player2;
    GdiLedStrips    _gdiLedStrips;
    GdiLed          _gdiPauseLed;
    GdiLed          _gdiSelectLed;
    GdiLed          _gdiSetupLed;
    GdiLed          _gdiPlayer1Led;
    GdiLed          _gdiPlayer2Led;

    HWND _hwnd;
	HDC _memDC;	
	HBITMAP _memBitmap;
    
    HBRUSH _enclosureBrush;

    uint16_t D(
        uint16_t value) const;
};
