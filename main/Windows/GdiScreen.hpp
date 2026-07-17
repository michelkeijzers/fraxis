#pragma once

#include "Components/GdiLedStrips.hpp"
#include "Components/GdiLcd1602Display.hpp"
#include "Components/GdiSevenDigitsDisplay.hpp"
#include "Components/GdiLed.hpp"
#include "IGdiMouseInput.hpp"
#include <string>
#include <windows.h>
#include <vector>
#include <memory>

class LedStripModel;
class Lcd1602DisplayModel;
class Tm1637Model;
class PinIo;
class WindowsMcp23017;
class WindowsTm1637;


class GdiScreen
{
public:
    GdiScreen(
        LedStripModel* ledStripModel,
        Lcd1602DisplayModel* lcd1602DisplayModel,
        Tm1637Model* tm1637CentralPanel,
        Tm1637Model* tm1637Player1,
        Tm1637Model* tm1637Player2,
        PinIo* pinIo,
        WindowsMcp23017* windowsMcp23017
    );

	void CreateMemoryDc(HWND hwnd, int width, int height);

	void Update();
    void UpdateLedStrips();
    void UpdateLcd1602Display();
    void UpdateTm1637();

	HDC GetMemDC() { return _memDC; }

	int D(int value) { return value * 2; } // Placeholder for scaling function)

	GdiLedStrips& GetLedStrips() { return _gdiLedStrips; }

	void OnMouseDown(int x, int y);
	void OnMouseMove(int x, int y);
	void OnMouseUp(int x, int y);
	
    LedStripModel& GetLedStripModel() { return *_ledStripModel; }

private:
	HDC _memDC;	
	HBITMAP _memBitmap;

    LedStripModel* _ledStripModel;
    Lcd1602DisplayModel* _lcd1602DisplayModel;
    Tm1637Model* _tm1637ModelCentralPanel;
    Tm1637Model* _tm1637ModelPlayer1;
    Tm1637Model* _tm1637ModelPlayer2;

	PinIo& _pinIo;
	WindowsMcp23017& _windowsMcp23017;

	GdiLedStrips _gdiLedStrips;
    GdiLcd1602Display _gdiLcd1602Display;
	GdiSevenDigitsDisplay _gdiSevenDigitsDisplayCentralPanel;
	GdiSevenDigitsDisplay _gdiSevenDigitsDisplayPlayer1;
	GdiSevenDigitsDisplay _gdiSevenDigitsDisplayPlayer2;

    GdiLed _gdiPauseLed;
    GdiLed _gdiSelectLed;
    GdiLed _gdiSetupLed;
    GdiLed _gdiPlayer1Led;
    GdiLed _gdiPlayer2Led;

	std::vector<std::unique_ptr<IGdiMouseInput>> _gdiMouseInputs;

    HWND _hwnd;

    bool _updateLedStrips;
    bool _updateLcd1602Display;
    bool _updateTm1637;

public: 
    HWND GetHwnd() const { return _hwnd; }
};
