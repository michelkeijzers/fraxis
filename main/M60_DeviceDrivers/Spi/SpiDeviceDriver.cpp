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

// Do not make =default in .hpp file because of unique_ptr needing complete (sub) types.
SpiDeviceDriver::~SpiDeviceDriver() = default;

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
        frequency == 100'000 || frequency == 400'000,  // NOSONAR TODO SPI
        "Spi Frequency should be xxx 100 or 400 KHz"); // NOSONAR TODO SPI

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
    Assert::IsTrue(
        Types::ETaskId::SpiTask, GetSpi().IsValidPort(port), "SPI Port should be xxx"); 
    // NOSONAR TODO SPI
}

void SpiDeviceDriver::Initialize()
{
    //_csPin = -1; // NOSONAR TODO SPI
    Assert::IsTrue(
        Types::ETaskId::SpiTask, 
        GetSpi().ParamConfig(_port, _mosiPin, _misoPin, _sclkPin, _frequency),
    "Failed to param config");
    Assert::IsTrue(
        Types::ETaskId::SpiTask, 
        GetSpi().DriverInstall(_port), 
        "Failed to install SPI driver");

    MarkInitialized();
}

// NOSONAR TODO SPI
// void SpiDeviceDriver::Write(
//     uint8_t deviceAddress, 
//     const uint8_t* data, 
//     size_t length)
// {
//     Assert::IsTrue(
//         Types::ETaskId::SpiTask, IsInitialized());
//     Assert::IsTrue(
//         Types::ETaskId::SpiTask, 
//         //GetI2c().MasterWriteToDevice(_port, deviceAddress, data, length, 1000), 
//         "Failed to write to device");
// }
//
// void SpiDeviceDriver::Read(
//     uint8_t deviceAddress,
//     uint8_t* data,
//     size_t length)
// {
//     Assert::IsTrue(
//         Types::ETaskId::I2cTask, IsInitialized());
//     Assert::IsTrue(
//         Types::ETaskId::I2cTask, 
//         GetI2c().MasterReadFromDevice(_port, deviceAddress, data, length, 1000), 
//         "Failed to read from device");
// }
