#pragma once

#include <cstdint>
#include "../Components/AtariJoystick.hpp"


enum class EInput 
{
    NONE, 
    SYSTEM_BUTTON,
    P1_UP,
    P1_DOWN, 
    P1_LEFT,
    P1_RIGHT,
    P1_BUTTON,
    P2_BUTTON,
    P2_UP,
    P2_DOWN,
    P2_LEFT,
    P2_RIGHT
};

class MenuInput 
{
public:
	MenuInput();
	~MenuInput();

   EInput readInput();
	void SetJoystickState(AtariJoystick::EId joystickId, uint8_t pressedItems);
	void SetSystemButtonState(bool pressed);
	
private:
	uint8_t _previousJoystickStates[2];
	uint8_t _joystickStates[2];

	bool _previousSystemButtonState;
	bool _systemButtonState;
};
