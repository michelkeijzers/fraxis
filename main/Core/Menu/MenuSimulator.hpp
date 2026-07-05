#pragma once

#include "MenuRenderer.hpp"
#include "MenuStates.hpp"

class IRtos;
class IRtosQueue;

class Lcd1602Display;
class Tm1637;
class PinIo;
class MenuInput;

class MenuSimulator {
public:
    MenuSimulator(IRtos& rtos, IRtosQueue& rtosQueue, Lcd1602Display& lcdDisplay, PinIo& pinIo, 
		 Tm1637& tm1637CentralPanel, Tm1637& tm1637Player1, Tm1637& tm1637Player2);

    void Initialize();

    MenuInput& GetMenuInput() { return _menuInput; }
    void run();

private:
    void Output(const MenuRenderer::Result& result);

    IRtos& _rtos;
    IRtosQueue& _rtosQueue;

	Lcd1602Display& _lcdDisplay;
    PinIo& _pinIo;
    Tm1637& _tm1637CentralPanel;
    Tm1637& _tm1637Player1;
    Tm1637& _tm1637Player2;

    MenuInput _menuInput;
    MenuRenderer _renderer;
    MenuStates _menuStates;
};
