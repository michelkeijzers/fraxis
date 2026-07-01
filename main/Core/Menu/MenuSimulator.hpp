#pragma once

#include "MenuRenderer.hpp"
#include "MenuStates.hpp"

class Lcd1602Display;
class PinIo;
class MenuInput;

class MenuSimulator {
public:
    MenuSimulator(Lcd1602Display& lcdDisplay, PinIo& pinIo);

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
};
