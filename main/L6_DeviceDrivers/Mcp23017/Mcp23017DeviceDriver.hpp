#pragma once

#include "../DeviceDriver.hpp"

class I2cDeviceDriver;

class Mcp23017DeviceDriver : public DeviceDriver
{
public:
    Mcp23017DeviceDriver();
    ~Mcp23017DeviceDriver();

    void SetI2cDeviceDriver(I2cDeviceDriver& i2cDeviceDriver);

    void Initialize() override;
    
private:
    I2cDeviceDriver* _i2cDeviceDriver;     
};

