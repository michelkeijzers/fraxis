#pragma once

#include "../DeviceDriver.hpp"
#include <cstdint>

class I2cDeviceDriver;

class Mcp23017DeviceDriver : public DeviceDriver
{
public:
    Mcp23017DeviceDriver();
    ~Mcp23017DeviceDriver();

    void SetI2cDeviceDriver(I2cDeviceDriver& i2cDeviceDriver);

    void Initialize() override;
    
protected:
    I2cDeviceDriver& GetI2cDeviceDriver();
    uint8_t GetI2cAddress();

private:
    I2cDeviceDriver* _i2cDeviceDriver;     
    uint8_t _i2cAddress;
};

