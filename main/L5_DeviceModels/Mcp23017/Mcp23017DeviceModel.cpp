#include "Mcp23017DeviceModel.hpp"
#include "../../L9_Utilities/Assert/Assert.hpp"

Mcp23017DeviceModel::Mcp23017DeviceModel()
: _i2cAddress(0), _inputPinsMask(0), _gpioStates(0)

{
}

Mcp23017DeviceModel::~Mcp23017DeviceModel()
{
}

uint8_t Mcp23017DeviceModel::GetI2cAddress() const
{
    return _i2cAddress;
}

void Mcp23017DeviceModel::SetI2cAddress(uint8_t i2cAddress)
{
    _i2cAddress = i2cAddress;
}

void Mcp23017DeviceModel::SetInputBits(std::list<uint8_t> inputBits)
{
    _inputPinsMask = 0;
    for (auto bit : inputBits)
    {
        _inputPinsMask |= (1 << bit);
    }
}

void Mcp23017DeviceModel::Initialize()
{
    MarkInitialized();
}

uint16_t Mcp23017DeviceModel::GetInputPinsMask() const
{
    return _inputPinsMask;
}

uint16_t Mcp23017DeviceModel::GetGpioStates() const
{
    return _gpioStates;
}

/// @brief Sets the GPIO states.
/// @details The GPIO states are set by theI2c driver delegate in L6 DeviceDrivers layer, after an MCP23017 interrupt
/// has been triggered..
void Mcp23017DeviceModel::SetGpioStates(uint16_t gpioStates)
{
    _gpioStates = gpioStates;
}

bool Mcp23017DeviceModel::GetInputBit(uint8_t bit) const
{
    Assert::IsTrue(IsInitialized());
    Assert::IsTrue((_inputPinsMask & (1 << bit)) != 0, "bit is not an input pin");

    return (_gpioStates & (1 << bit)) != 0;
}

void Mcp23017DeviceModel::SetOutputBit(uint8_t bit, bool state)
{
    Assert::IsTrue(IsInitialized());
    Assert::IsFalse((_inputPinsMask & (1 << bit)) != 0, "bit is not an output pin");
    
    uint16_t oldGpioStates = _gpioStates;
    if (state)
    {
        _gpioStates |= (1 << bit);
    }
    else
    {
        _gpioStates &= ~(1 << bit);
    }

    if (oldGpioStates != _gpioStates)
    {
        MarkDirty();
    }
}
