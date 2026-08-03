#pragma once

#include "../DeviceDriver.hpp"
#include <cstdint>
#include <cstddef>

class I2c;

class I2cDeviceDriver : public DeviceDriver
{
public:
    I2cDeviceDriver();
    ~I2cDeviceDriver();

    void SetI2c(
        I2c& i2c);
    void SetConfiguration(
        uint8_t port,
        uint8_t sdaPin, 
        uint8_t sclPin, 
        uint32_t frequency);
    void Initialize() override;

    void Read(
        uint8_t deviceAddress,
        uint8_t* data,
        size_t length);
    void Write(
        uint8_t deviceAddress,
        const uint8_t* data, 
        size_t length);

    uint8_t ReadRegister(uint8_t deviceAddress,
        uint8_t registerAddress);
    void ReadRegister(uint8_t deviceAddress,
        uint8_t registerAddress,
        uint8_t* data,
        size_t length);
    void WriteRegister(uint8_t deviceAddress,
        uint8_t registerAddress,
        uint8_t data);
    void WriteRegister(uint8_t deviceAddress,
        uint8_t registerAddress, 
        const uint8_t* data,
        size_t length);

private:
    void AssertValidPort(
        uint8_t port);

    I2c& GetI2c();

    uint8_t _port;
    uint8_t _sdaPin;
    uint8_t _sclPin;
    uint32_t _frequency;
    I2c* _i2c;
};
