#include "Mcp23017Model.hpp"

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
