#pragma once

#include "../DeviceDriver.hpp"
#include <stdint.h>
#include <cstddef>

class I2cDeviceDriver : public DeviceDriver
{
public:
    I2cDeviceDriver();
    ~I2cDeviceDriver();

    virtual void SetConfiguration(uint8_t i2cPort, uint8_t sdaPin, uint8_t sclPin, uint32_t i2cFrequency) = 0;

    virtual void Read(uint8_t deviceAddress, uint8_t* data, size_t length) = 0;
    virtual void Write(uint8_t deviceAddress, const uint8_t* data, size_t length) = 0;

    virtual void ReadRegister(uint8_t deviceAddress, uint8_t registerAddress, uint8_t* data, size_t length) = 0;
    virtual void WriteRegister(uint8_t deviceAddress, uint8_t registerAddress, const uint8_t* data, size_t length) = 0;    
};
