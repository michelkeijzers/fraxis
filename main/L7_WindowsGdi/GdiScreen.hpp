#pragma once

#include "Components/GdiLcd2004.hpp"
#include "Components/GdiTm1637.hpp"
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
    void UpdateTm1637CentralPanel();
    void UpdateTm1637Player1();
    void UpdateTm1637Player2();

private:
    void UpdateEnclosure();

    GdiLcd2004 _gdiLcd2004;
    GdiTm1637 _gdiTm1637CentralPanel;
    GdiTm1637 _gdiTm1637Player1;
    GdiTm1637 _gdiTm1637Player2;

    HWND _hwnd;
	HDC _memDC;	
	HBITMAP _memBitmap;

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
////
////    GdiLed _gdiPauseLed;
////    GdiLed _gdiSelectLed;
////    GdiLed _gdiSetupLed;
////    GdiLed _gdiPlayer1Led;
////    GdiLed _gdiPlayer2Led;
////
////	std::vector<std::unique_ptr<IGdiMouseInput>> _gdiMouseInputs;
