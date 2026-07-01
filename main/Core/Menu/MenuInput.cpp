#include "MenuInput.hpp"
#include "MenuSimulator.hpp"
#include "../Components/PinIo.hpp"

MenuInput::MenuInput(PinIo& pinIo) : _pinIo(pinIo)
{
}

MenuInput::~MenuInput()
{
}

EInput MenuInput::ReadInput() 
{
	_pinIo.Update();

	EInput input = EInput::NONE;
	if (_pinIo.IsSystemButtonPressed()) input = EInput::SYSTEM_BUTTON;
	else if (_pinIo.GetJoystickDirection(PinIo::EPlayerId::Player1) == PinIo::EJoystickDirection::Up) input = EInput::P1_UP;
	else if (_pinIo.GetJoystickDirection(PinIo::EPlayerId::Player1) == PinIo::EJoystickDirection::Down) input = EInput::P1_DOWN;
	else if (_pinIo.GetJoystickDirection(PinIo::EPlayerId::Player1) == PinIo::EJoystickDirection::Left) input = EInput::P1_LEFT;
	else if (_pinIo.GetJoystickDirection(PinIo::EPlayerId::Player1) == PinIo::EJoystickDirection::Right) input = EInput::P1_RIGHT;
	else if (_pinIo.GetJoystickButton(PinIo::EPlayerId::Player1)) input = EInput::P1_BUTTON;
	return input;
}
