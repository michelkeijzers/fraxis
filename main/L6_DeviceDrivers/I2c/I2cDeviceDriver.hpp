#pragma once

#include "../DeviceDriver.hpp"
#include <cstdint>
#include <cstddef>

class I2cDeviceDriver : public DeviceDriver
{
public:
    I2cDeviceDriver();
    ~I2cDeviceDriver();

    void SetConfiguration(uint8_t port, uint8_t sdaPin, uint8_t sclPin, uint32_t frequency);

    virtual void Read(uint8_t deviceAddress, uint8_t* data, size_t length) = 0;
    virtual void Write(uint8_t deviceAddress, const uint8_t* data, size_t length) = 0;

    virtual uint8_t ReadRegister(uint8_t deviceAddress, uint8_t registerAddress) = 0;
    virtual void ReadRegister(uint8_t deviceAddress, uint8_t registerAddress, uint8_t* data, size_t length) = 0;
    virtual void WriteRegister(uint8_t deviceAddress, uint8_t registerAddress, uint8_t data) = 0;
    virtual void WriteRegister(uint8_t deviceAddress, uint8_t registerAddress, const uint8_t* data, size_t length) = 0;    

protected:
    virtual void AssertValidPort(uint8_t port) = 0;

    uint8_t GetPort() const;
    uint8_t GetSdaPin() const;
    uint8_t GetSclPin() const;
    uint32_t GetFrequency() const;

private:
    uint8_t _port;
    uint8_t _sdaPin;
    uint8_t _sclPin;
    uint32_t _frequency;
};
