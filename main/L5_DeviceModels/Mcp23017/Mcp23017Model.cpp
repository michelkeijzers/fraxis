#include "Mcp23017Model.hpp"

Mcp23017Model::Mcp23017Model()
{
}

Mcp23017Model::~Mcp23017Model()
{
}

uint8_t Mcp23017Model::GetI2cAddress() const
{
    return _i2cAddress;
}

void Mcp23017Model::SetI2cAddress(uint8_t i2cAddress)
{
    _i2cAddress = i2cAddress;
}

void Mcp23017Model::SetInputBits(std::list<uint8_t> inputBits)
{
    _inputPinsMask = 0;
    for (auto bit : inputBits)
    {
        _inputPinsMask |= (1 << bit);
    }
}

void Mcp23017Model::Initialize()
{
}

uint16_t Mcp23017Model::GetInputPinsMask() const
{
    return _inputPinsMask;
}

uint16_t Mcp23017Model::GetGpioStates() const
{
    return _gpioStates;
}
