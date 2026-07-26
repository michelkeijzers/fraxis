#pragma once

#include "I2cDeviceDriver.hpp"
#include "driver/i2c.h"

class EspI2cDeviceDriver : public I2cDeviceDriver
{
public:
    EspI2cDeviceDriver();
    ~EspI2cDeviceDriver();

    void SetConfiguration(uint8_t i2cPort, uint8_t sdaPin, uint8_t sciPin, uint32_t i2cFrequency) override;
    void Initialize() override;
    
    void Read(uint8_t deviceAddress, uint8_t* data, size_t length) override;
    void Write(uint8_t deviceAddress, const uint8_t* data, size_t length) override;

    void ReadRegister(uint8_t deviceAddress, uint8_t registerAddress, uint8_t* data, size_t length) override;
    void WriteRegister(uint8_t deviceAddress, uint8_t registerAddress, const uint8_t* data, size_t length) override;

private:
    i2c_port_t _i2cPort;
    gpio_num_t _sdaPin;
    gpio_num_t _sclPin;
    uint32_t _i2cFrequency;
};
