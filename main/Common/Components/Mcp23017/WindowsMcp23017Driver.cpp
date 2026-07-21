#include "WindowsMcp23017Driver.hpp"
#include "../../../Core/Components/PinIoMappings.hpp"
#include "../../Services/Debug/Debug.hpp"

WindowsMcp23017Driver::WindowsMcp23017Driver(Mcp23017Model& model, I2c& i2c) 
: Mcp23017Driver(model, i2c)
{
}

void WindowsMcp23017Driver::Initialize()
{
    SendInputPinsMask();
}

void WindowsMcp23017Driver::SendInputPinsMask()
{
}

uint16_t WindowsMcp23017Driver::ReadGpio()
{
    uint8_t portA = _gpioStates >> 8;
    uint8_t portB = 0;

    return (static_cast<uint16_t>(portA) << 8) | portB;
}

/// TODO
// void Mcp23017Driver::WriteGpio(uint16_t gpioStates)
// {
//     uint8_t portA = (gpioStates >> 8) & 0xFF;
//     uint8_t portB = gpioStates & 0xFF;

//     //TODO: SET IN MODEL (SetPinForWIndows?)
// }

//TODO: MOVE TO HIGHER LEVEL (?)
void WindowsMcp23017Driver::SimulateSetGpioPin(PinIoMappings::EIdBit idBit, uint8_t value)
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

// TODO: MOVE TO HIGHER LEVEL
void WindowsMcp23017Driver::SimulateResetGpioPins()
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
