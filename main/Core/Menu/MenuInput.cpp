#include "MenuInput.hpp"
#include "MenuSimulator.hpp"
#include "../Components/AtariJoystick.hpp"

MenuInput::MenuInput()
	: _previousJoystickStates{ 0, 0 },
	_joystickStates{ 0, 0 },
	_previousSystemButtonState(false),
	_systemButtonState(false)
{
}

MenuInput::~MenuInput()
{
}

EInput MenuInput::readInput() 
{
	uint8_t systemButtonChanged = _systemButtonState != _previousSystemButtonState;
	if (systemButtonChanged)
	{
		_previousSystemButtonState = _systemButtonState;
		if (_systemButtonState)
		{
			return EInput::SYSTEM_BUTTON;
		}
	}

	uint8_t changed = _joystickStates[0] ^ _previousJoystickStates[0];
	if (changed)
	{
		_previousJoystickStates[0] = _joystickStates[0];
		if (_joystickStates[0] & 0x01) return EInput::P1_UP;
		if (_joystickStates[0] & 0x02) return EInput::P1_DOWN;
		if (_joystickStates[0] & 0x04) return EInput::P1_LEFT;
		if (_joystickStates[0] & 0x08) return EInput::P1_RIGHT;
		if (_joystickStates[0] & 0x10) return EInput::P1_BUTTON;
	}

	return EInput::NONE;
}

void MenuInput::SetJoystickState(AtariJoystick::EId joystickId, uint8_t pressedItems)
{
	_joystickStates[static_cast<int>(joystickId)] = pressedItems;
}

void MenuInput::SetSystemButtonState(bool pressed)
{
	_systemButtonState = pressed;
}
