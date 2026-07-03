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


void WindowsMcp23017::SimulateSetGpioPin(PinIoMappings::EId id, uint8_t value)
{
	uint16_t currentGpioStates = GetGpioStates();
	uint8_t pinIndex = (PinIoMappings::GetPort(id) * 8) + PinIoMappings::GetPin(id);
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
	SimulateSetGpioPin(PinIoMappings::EId::SystemButton, 0);

	SimulateSetGpioPin(PinIoMappings::EId::Player1Up, 0);
	SimulateSetGpioPin(PinIoMappings::EId::Player1Down, 0);
	SimulateSetGpioPin(PinIoMappings::EId::Player1Left, 0);
	SimulateSetGpioPin(PinIoMappings::EId::Player1Right, 0);
	SimulateSetGpioPin(PinIoMappings::EId::Player1Button, 0);

	SimulateSetGpioPin(PinIoMappings::EId::Player2Up, 0);
	SimulateSetGpioPin(PinIoMappings::EId::Player2Down, 0);
	SimulateSetGpioPin(PinIoMappings::EId::Player2Left, 0);
	SimulateSetGpioPin(PinIoMappings::EId::Player2Right, 0);
	SimulateSetGpioPin(PinIoMappings::EId::Player2Button, 0);
}