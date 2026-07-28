#include "Mcp23017DeviceModel.hpp"

Mcp23017DeviceModel::Mcp23017DeviceModel()
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
}

uint16_t Mcp23017DeviceModel::GetInputPinsMask() const
{
    return _inputPinsMask;
}

uint16_t Mcp23017DeviceModel::GetGpioStates() const
{
    return _gpioStates;
}

void Mcp23017DeviceModel::SetOutputBit(uint16_t bit, bool state)
{
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
