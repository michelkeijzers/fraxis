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


void WindowsMcp23017::SimulateSetGpioPin(PinIoMappings::EIdBit idBit, uint8_t value)
{
	uint16_t currentGpioStates = GetGpioStates();
    uint16_t newGpioStates = currentGpioStates;
    int16_t idValue = 1 << (uint16_t)idBit;
	if (value == 0)
	{
        newGpioStates &= ~idValue;
	}
	else
	{
        newGpioStates |= idValue;
	}
    SetGpioStates(newGpioStates);
}

void WindowsMcp23017::SimulateResetGpioPins()
{
	SimulateSetGpioPin(PinIoMappings::EIdBit::SystemButton, 0);

	SimulateSetGpioPin(PinIoMappings::EIdBit::Player1Up, 0);
	SimulateSetGpioPin(PinIoMappings::EIdBit::Player1Down, 0);
	SimulateSetGpioPin(PinIoMappings::EIdBit::Player1Left, 0);
	SimulateSetGpioPin(PinIoMappings::EIdBit::Player1Right, 0);
	SimulateSetGpioPin(PinIoMappings::EIdBit::Player1Button, 0);

	SimulateSetGpioPin(PinIoMappings::EIdBit::Player2Up, 0);
	SimulateSetGpioPin(PinIoMappings::EIdBit::Player2Down, 0);
	SimulateSetGpioPin(PinIoMappings::EIdBit::Player2Left, 0);
	SimulateSetGpioPin(PinIoMappings::EIdBit::Player2Right, 0);
	SimulateSetGpioPin(PinIoMappings::EIdBit::Player2Button, 0);
}