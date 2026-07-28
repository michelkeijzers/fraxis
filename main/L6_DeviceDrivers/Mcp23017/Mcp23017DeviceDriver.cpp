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

I2cDeviceDriver& Mcp23017DeviceDriver::GetI2cDeviceDriver() 
{
    return *_i2cDeviceDriver; 
}


uint8_t Mcp23017DeviceDriver::GetI2cAddress() 
{
    return _i2cAddress; 
}
