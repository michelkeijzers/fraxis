#pragma once

#include <windows.h>

class GdiScreen
{
public:
    GdiScreen();
    ~GdiScreen();

    HDC GetMemDc();

    void CreateMemoryDc(HWND hwnd, int width, int height);
    void Update();

private:
    void UpdateEnclosure();

    HWND _hwnd;
	HDC _memDC;	
	HBITMAP _memBitmap;

    int D(int value);
};

//#include "Components/GdiLedStrips.hpp"
//#include "Components/GdiLcd1602Display.hpp"
////#include "Components/GdiSevenDigitsDisplay.hpp"
//#include "Components/GdiLed.hpp"
//#include "IGdiMouseInput.hpp"
//#include <string>
//#include <vector>
//#include <memory>
//
////class Ws28xxDeviceModel;
////class Lcd1602DisplayModel;
////class Tm1637DeviceModel;
////class PinIo;
////class WindowsMcp23017;
////class WindowsTm1637;
//
//
//class GdiScreen
//{
//public:
//    GdiScreen(
//        //Ws28xxDeviceModel* ws28xxDeviceModel,
//        //Lcd1602DisplayModel* lcd1602DisplayModel,
//        //Tm1637DeviceModel* tm1637CentralPanel,
//        //Tm1637DeviceModel* tm1637Player1,
//        //Tm1637DeviceModel* tm1637Player2,
//        //PinIo* pinIo,
//        //WindowsMcp23017* windowsMcp23017
//    );
//
////
////	void Update();
////    void UpdateLedStrips();
////    void UpdateLcd1602Display();
////    void UpdateTm1637();
////
////	HDC GetMemDC() { return _memDC; }
////
////	int D(int value) { return value * 2; } // Placeholder for scaling function)
////
//////	GdiLedStrips& GetLedStrips() { return _gdiLedStrips; }
////
////	void OnMouseDown(int x, int y);
////	void OnMouseMove(int x, int y);
////	void OnMouseUp(int x, int y);
////	
////    Ws28xxDeviceModel& GetWs28xxDeviceModel() { return *_ws28xxDeviceModel; }
////
////private:
////
////    Ws28xxDeviceModel* _ws28xxDeviceModel;
////    Lcd1602DisplayModel* _lcd1602DisplayModel;
////    Tm1637DeviceModel* _tm1637DeviceModelCentralPanel;
////    Tm1637DeviceModel* _tm1637DeviceModelPlayer1;
////    Tm1637DeviceModel* _tm1637DeviceModelPlayer2;
////
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
////
////    bool _updateLedStrips;
////    bool _updateLcd1602Display;
////    bool _updateTm1637;
////
////public: 
////    HWND GetHwnd() const { return _hwnd; }
//};
