#include "I2cDeviceDriver.hpp"
#include "../../L9_Utilities/Assert/Assert.hpp"

I2cDeviceDriver::I2cDeviceDriver()
{
}

I2cDeviceDriver::~I2cDeviceDriver()
{
}

void I2cDeviceDriver::SetConfiguration(uint8_t port, uint8_t sdaPin, uint8_t sclPin, uint32_t frequency)
{
    AssertValidPort(port);
    Assert::IsTrue(frequency == 100'000 || frequency == 400'000, "i2c Frequency should be 100 or 400 KHz");

    _port = port;
    _sdaPin = sdaPin;
    _sclPin = sclPin;
    _frequency = frequency;
}

uint8_t I2cDeviceDriver::GetPort() const
{
    return _port;
}

uint8_t I2cDeviceDriver::GetSdaPin() const
{
    return _sdaPin;
}

uint8_t I2cDeviceDriver::GetSclPin() const
{
    return _sclPin;
}

uint32_t I2cDeviceDriver::GetFrequency() const
{
    return _frequency;
}
