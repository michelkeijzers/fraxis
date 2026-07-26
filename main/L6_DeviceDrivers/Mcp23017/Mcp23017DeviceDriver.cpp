#include "Mcp23017DeviceDriver.hpp"

Mcp23017DeviceDriver::Mcp23017DeviceDriver()
{
}

Mcp23017DeviceDriver::~Mcp23017DeviceDriver()
{
}

void Mcp23017DeviceDriver::Initialize()
{
    // TODO
}

void Mcp23017DeviceDriver::SetI2cDeviceDriver(I2cDeviceDriver& i2cDeviceDriver)
{
    _i2cDeviceDriver = &i2cDeviceDriver; 
}
