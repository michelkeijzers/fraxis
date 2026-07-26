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

void Mcp23017Model::Initialize()
{
}
