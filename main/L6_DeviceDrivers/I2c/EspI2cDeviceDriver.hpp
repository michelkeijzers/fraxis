#ifdef ESP_PLATFORM

#pragma once

#include "I2cDeviceDriver.hpp"
#include "driver/i2c.h"
#include "driver/gpio.h"
#include <cstdint>

class EspI2cDeviceDriver : public I2cDeviceDriver
{
public:
    EspI2cDeviceDriver();
    ~EspI2cDeviceDriver();

    void AssertValidPort(uint8_t i2cPort) override;

    void Initialize() override;
    
    i2c_port_t GetPort() const;
    gpio_num_t GetSdaPin() const;
    gpio_num_t GetSclPin() const;

    void Read(uint8_t deviceAddress, uint8_t* data, size_t length) override;
    void Write(uint8_t deviceAddress, const uint8_t* data, size_t length) override;

    uint8_t ReadRegister(uint8_t deviceAddress, uint8_t registerAddress) override;
    void ReadRegister(uint8_t deviceAddress, uint8_t registerAddress, uint8_t* data, size_t length) override;
    void WriteRegister(uint8_t deviceAddress, uint8_t registerAddress, const uint8_t* data, size_t length) override;
    void WriteRegister(uint8_t deviceAddress, uint8_t registerAddress, uint8_t data) override;
};

#endif // ESP_PLATFORM
