#include "SpiDeviceDriver.hpp"
#include "../../M90_Utilities/Assert/Assert.hpp"
#include "../../M80_Services/Spi/Spi.hpp"

SpiDeviceDriver::SpiDeviceDriver()
:
    _port(0),
    _mosiPin(0),
    _misoPin(0),
    _sclkPin(0),
    _frequency(0),
    _spi(nullptr)
{
}

void SpiDeviceDriver::SetConfiguration(
    uint8_t port,
    uint8_t mosiPin,
    uint8_t misoPin,
    uint8_t sclkPin,
    uint32_t frequency)
{
    AssertValidPort(port);
    Assert::IsTrue(
        Types::ETaskId::SpiTask, 
        frequency == 100'000 || frequency == 400'000,  //TODOSPI
        "Spi Frequency should be xxx 100 or 400 KHz"); // TODOSPI

    _port = port;
    _mosiPin = mosiPin;
    _misoPin = misoPin;
    _sclkPin = sclkPin;
    _frequency = frequency;
}

Spi& SpiDeviceDriver::GetSpi()
{
    return *_spi;
}

void SpiDeviceDriver::SetSpi(
    Spi& spi)
{
    _spi = &spi;
}

void SpiDeviceDriver::AssertValidPort(
    uint8_t port)
{
    Assert::IsTrue(Types::ETaskId::SpiTask, GetSpi().IsValidPort(port), "SPI Port should be xxx"); // TODOSPI
}

void SpiDeviceDriver::Initialize()
{
    //_csPin = -1; // TODOSPI
    Assert::IsTrue(
        Types::ETaskId::SpiTask, GetSpi().ParamConfig(_port, _mosiPin, _misoPin, _sclkPin, _frequency));
    Assert::IsTrue(
        Types::ETaskId::SpiTask, GetSpi().DriverInstall(_port));

    MarkInitialized();
}
    
// void SpiDeviceDriver::Write(
//     uint8_t deviceAddress, 
//     const uint8_t* data, 
//     size_t length)
// {
//     Assert::IsTrue(
//         Types::ETaskId::SpiTask, IsInitialized());
//     Assert::IsTrue(
//         Types::ETaskId::SpiTask, 
//         //GetI2c().MasterWriteToDevice(_port, deviceAddress, data, length, 1000), "Failed to write to device");
// }

// void SpiDeviceDriver::Read(
//     uint8_t deviceAddress,
//     uint8_t* data,
//     size_t length)
// {
//     Assert::IsTrue(
//         Types::ETaskId::I2cTask, IsInitialized());
//     Assert::IsTrue(
//         Types::ETaskId::I2cTask, 
//         GetI2c().MasterReadFromDevice(_port, deviceAddress, data, length, 1000), "Failed to read from device");
// }
