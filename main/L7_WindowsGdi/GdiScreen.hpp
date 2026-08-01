#pragma once

#include "Components/GdiLcd2004.hpp"
#include <windows.h>

class DeviceModelsContext;

class GdiScreen
{
public:
    GdiScreen(DeviceModelsContext& deviceModelsContext);
    ~GdiScreen();

    HDC GetMemDc();

    void CreateMemoryDc(HWND hwnd, int width, int height);
    void Update();

    void UpdateLcd2004();

private:
    void UpdateEnclosure();

    GdiLcd2004 _gdiLcd2004;

    HWND _hwnd;
	HDC _memDC;	
	HBITMAP _memBitmap;

    DeviceModelsContext& _deviceModelsContext;

    int D(int value);
};

//#include "IGdiMouseInput.hpp"
//#include <string>
//#include <vector>
//#include <memory>
//
//class GdiScreen
//{
//public:
////	void OnMouseDown(int x, int y);
////	void OnMouseMove(int x, int y);
////	void OnMouseUp(int x, int y);
///
////private:
////	PinIo& _pinIo;
////	WindowsMcp23017& _windowsMcp23017;
////
////	GdiLedStrips _gdiLedStrips;
////    GdiLcd1602Display _gdiLcd1602Display;
////	GdiSevenDigitsDisplay _gdiSevenDigitsDisplayCentralPanel;
////	GdiSevenDigitsDisplay _gdiSevenDigitsDisplayPlayer1;
////	GdiSevenDigitsDisplay _gdiSevenDigitsDisplayPlayer2;
////
////    GdiLed _gdiPauseLed;
////    GdiLed _gdiSelectLed;
////    GdiLed _gdiSetupLed;
////    GdiLed _gdiPlayer1Led;
////    GdiLed _gdiPlayer2Led;
////
////	std::vector<std::unique_ptr<IGdiMouseInput>> _gdiMouseInputs;
