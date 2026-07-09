#include "WindowsMcp23017.hpp"
#include "../../Core/Components/PinIoMappings.hpp"
#include "../../Common/SharedUtils/Debug.hpp"

WindowsMcp23017::WindowsMcp23017() 
: _gpioStates(0), _ioDirectionPortA(0), _ioDirectionPortB(0)
{}

WindowsMcp23017::~WindowsMcp23017()
{}

void WindowsMcp23017::Initialize()
{}

void WindowsMcp23017::SetDirectionBytes(uint8_t ioDirectionPortA, uint8_t ioDirectionPortB)
{
    _ioDirectionPortA = ioDirectionPortA;
    _ioDirectionPortB = ioDirectionPortB;
}

uint16_t WindowsMcp23017::UpdateInputsAndOutputs(uint16_t gpioStates)
{
    // Extract input bits from caller
    uint16_t inputMask =
        ((uint16_t)_ioDirectionPortB << 8) |
        ((uint16_t)_ioDirectionPortA);

    uint16_t inputBits = _gpioStates & inputMask;

    // Extract existing output bits from stored state
    uint16_t outputMask = ~inputMask;
    uint16_t outputBits = gpioStates & outputMask;

    // Combine: keep old outputs, update inputs
    _gpioStates = outputBits | inputBits;

    return _gpioStates;
}

void WindowsMcp23017::SimulateSetGpioPin(PinIoMappings::EIdBit idBit, uint8_t value)
{
    uint16_t newGpioStates = _gpioStates;
    int16_t idValue = 1 << (uint8_t)idBit;
	if (value == 0)
	{
        _gpioStates &= ~idValue;
	}
	else
	{
        _gpioStates |= idValue;
	}
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