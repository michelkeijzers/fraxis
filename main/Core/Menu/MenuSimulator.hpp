#pragma once

#include "MenuRenderer.hpp"
#include "MenuStates.hpp"

class Lcd1602Display;
class Tm1637;
class PinIo;
class MenuInput;

class MenuSimulator {
public:
    MenuSimulator(Lcd1602Display& lcdDisplay, PinIo& pinIo, 
		 Tm1637& tm1637CentralPanel, Tm1637& tm1637Player1, Tm1637& tm1637Player2);

    void Initialize();

    MenuInput& GetMenuInput() { return _menuInput; }
    void run();

private:
    void Output(const MenuRenderer::Result& result);

    MenuStates _menuStates;
    MenuInput _menuInput;
    MenuRenderer _renderer;

	Lcd1602Display& _lcdDisplay;
    PinIo& _pinIo;
    Tm1637& _tm1637CentralPanel;
    Tm1637& _tm1637Player1;
    Tm1637& _tm1637Player2;
};
