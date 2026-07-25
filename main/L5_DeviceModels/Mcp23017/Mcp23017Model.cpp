#include "Mcp23017Model.hpp"
#include "../DeviceSettings.hpp"

Mcp23017Model::Mcp23017Model()
{
}

Mcp23017Model::~Mcp23017Model()
{
}

void Mcp23017Model::SetI2cModel(I2cModel& i2cModel)
{
    _i2cModel = &i2cModel;
}

void Mcp23017Model::Initialize()
{
    _i2cAddress = DeviceSettings::I2C_ADDRESS_MCP23017; 
}
