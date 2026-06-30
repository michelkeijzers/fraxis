#pragma once


#include "MenuRenderer.hpp"
#include "MenuStates.hpp"

class Lcd1602Display;
class MenuInput;

class MenuSimulator {
private:
    MenuStates _menuStates;
    MenuInput _input;
    MenuRenderer _renderer;

public:
    MenuSimulator(Lcd1602Display& lcdDisplay);
    void SetJoystickState(AtariJoystick::EId joystickId, uint8_t pressedItems);
    void SetSystemButtonState(bool pressed);
	 MenuInput& GetMenuInput() { return _input; }
    void run();

private:
    void Output(const MenuRenderer::Result& result);

	 Lcd1602Display& _lcdDisplay;
};
