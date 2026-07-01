#include "WindowsMcp23017.hpp"
#include "../../Core/Components/PinIoMappings.hpp"

WindowsMcp23017::WindowsMcp23017()
{}

WindowsMcp23017::~WindowsMcp23017()
{}

void WindowsMcp23017::Initialize()
{}

void WindowsMcp23017::SetDirectionBytes(uint8_t iodira, uint8_t iodirb)
{}

/// <summary>
/// Windows version does not reset GPIO states as ESP32 does, so it will can be
/// programmatically set to any value. This is useful for testing and simulation.
/// </summary>
/// <returns></returns>
uint16_t WindowsMcp23017::GetGpioStates() const
{
	return _gpioStates;
}

/// <summary>
/// Windows version does set GPIO states also for input pins, so it can be
/// programmatically set to any value. This is useful for testing and simulation.
/// </summary>
/// <param name="states"></param>
void WindowsMcp23017::SetGpioStates(uint16_t states)
{
	_gpioStates = states;
}


void WindowsMcp23017::SimulateSetGpioPin(uint8_t port, uint8_t pin, uint8_t value)
{
	uint16_t currentGpioStates = GetGpioStates();
	uint8_t pinIndex = (port == 0 ? 0 : 8) + pin;
	uint16_t gpioStates = 0;
	if (value == 0)
	{
		gpioStates = currentGpioStates & ~(1 << pinIndex);
		SetGpioStates(gpioStates);
	}
	else
	{
		gpioStates = currentGpioStates | (1 << pinIndex);
		SetGpioStates(gpioStates);
	}
}

void WindowsMcp23017::SimulateResetGpioPins()
{
	SimulateSetGpioPin(PinIoMappings::SYSTEM_BUTTON_PORT, PinIoMappings::SYSTEM_BUTTON_PIN, 0);

	SimulateSetGpioPin(PinIoMappings::PLAYER_1_UP_PORT, PinIoMappings::PLAYER_1_UP_PIN, 0);
	SimulateSetGpioPin(PinIoMappings::PLAYER_1_DOWN_PORT, PinIoMappings::PLAYER_1_DOWN_PIN, 0);
	SimulateSetGpioPin(PinIoMappings::PLAYER_1_LEFT_PORT, PinIoMappings::PLAYER_1_LEFT_PIN, 0);
	SimulateSetGpioPin(PinIoMappings::PLAYER_1_RIGHT_PORT, PinIoMappings::PLAYER_1_RIGHT_PIN, 0);
	SimulateSetGpioPin(PinIoMappings::PLAYER_1_BUTTON_PORT, PinIoMappings::PLAYER_1_BUTTON_PIN, 0);

	SimulateSetGpioPin(PinIoMappings::PLAYER_2_UP_PORT, PinIoMappings::PLAYER_2_UP_PIN, 0);
	SimulateSetGpioPin(PinIoMappings::PLAYER_2_DOWN_PORT, PinIoMappings::PLAYER_2_DOWN_PIN, 0);
	SimulateSetGpioPin(PinIoMappings::PLAYER_2_LEFT_PORT, PinIoMappings::PLAYER_2_LEFT_PIN, 0);
	SimulateSetGpioPin(PinIoMappings::PLAYER_2_RIGHT_PORT, PinIoMappings::PLAYER_2_RIGHT_PIN, 0);
	SimulateSetGpioPin(PinIoMappings::PLAYER_2_BUTTON_PORT, PinIoMappings::PLAYER_2_BUTTON_PIN, 0);
}